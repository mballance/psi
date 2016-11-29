/*
 * classlib_native_exec_1.cpp
 *
 * Copyright 2016 Mentor Graphics Corporation
 * All Rights Reserved Worldwide
 *
 * Licensed under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in
 *  compliance with the License.  You may obtain a copy of
 *  the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in
 * writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.  See
 * the License for the specific language governing
 * permissions and limitations under the License.
 * 
 *
 *  Created on: May 11, 2016
 *      Author: ballance
 */
#include "pss_tests.h"

int refmodel_get_next_value() {
	return 27;
}

class top : public Component {
public:
	pss_component_ctor(top);

	class entry_point : public Action {
	public:
		pss_action_ctor(entry_point);

		Rand<Bit<7,0>>		pss_field(p1);
		Rand<Bit<31,0>>		pss_field(p2);
		Rand<Bit<31,0>>		pss_field(p3);
		Field<Bit<31,0>>	pss_field(p4);
		Field<Bit<31,0>>	pss_field(p5);

		Exec pre_solve_e {this, Exec::PreSolve};

		Exec post_solve_e {this, Exec::PostSolve};

		void pre_solve() {
			// Set p4 based on calling a generation-time method
			p4.set(refmodel_get_next_value());
		}

		void post_solve() {
			// Set p5 based on a calculated value
			p5.set(p1.get() + p2.get());
			p5.set(p1.get() + p2.get()+1);
		}
	};
	pss_type(entry_point);

};
pss_global_type(top);

/**
 * Test code
 */
void exec_model(IModel *model) {
	const char *initial =
R"(
		<values>
			<bit path="top.entry_point.p1">0x01</bit>
			<bit path="top.entry_point.p2">0x20</bit>
			<bit path="top.entry_point.p3">0x30</bit>
			<bit path="top.entry_point.p4">0x00</bit>
			<bit path="top.entry_point.p5">0x00</bit>
		</values>
)";

	InlineExecInitialValueTestFixture::run(
			model,
			"top",
			"entry_point",
			initial);
}
