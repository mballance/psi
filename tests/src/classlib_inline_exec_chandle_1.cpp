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

class my_class {
public:

	uint32_t get_value() { return 0x27; }
};

class top : public component {
public:
	pss_component_ctor(top);

	class entry_point : public action {
	public:
		pss_action_ctor(entry_point);

		chandle<my_class>			pss_field(p1);
		attr<uint32_t>				pss_field(p2);
		attr<chandle<>>				pss_field(p3);

		exec pre_solve_e {this, exec::PreSolve};

		exec post_solve_e {this, exec::PostSolve};

		void pre_solve() {
			p1.set(new my_class());
		}

		void post_solve() {
			p2.set(p1.get()->get_value());
			p3.set(0);
		}
	};
	pss_type(entry_point);

};
pss_type(top);

/**
 * Test code
 */
void exec_model(IModel *model) {
	const char *initial =
R"(
		<values>
			<chandle path="top.entry_point.p1">0</chandle>
			<bit path="top.entry_point.p2">0</bit>
			<chandle path="top.entry_point.p3">0x10001000</chandle>
		</values>
)";

	InlineExecInitialValueTestFixture::run(
			model,
			"top",
			"entry_point",
			initial);
}
