/*
 * classlis_dac_tutorial_data_flow.cpp
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
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#include "pss_tests.h"

class S : public pss_struct {
public:
	pss_ctor(S, pss_struct);

};
pss_type(S);

class CA : public component {
public:
	pss_ctor(CA, component);

	class A : public action {
	public:
		pss_ctor(A, action);

		output<S>			pss_field(out_s);
	};
	pss_type(A);

};
pss_type(CA);

class CB : public component {
public:
	pss_ctor(CB, component);

	class B : public action {
	public:
		pss_ctor(B, action);

		input<S>			pss_field(in_s);
	};
	pss_type(B);
};
pss_type(CB);

class static_structure : public component {
public:

	CA			ca1 {"ca1"};
	CA			ca2 {"ca2"};
	CB			cb1 {"cb1"};
	CB			cb2 {"cb2"};

	static_structure(const Scope &s) : component(this) {
		fprintf(stdout, "<--> static_structure %p\n", this);
	}

	bind b2 { this,
			ca1._A_t.out_s,
			ca2._A_t.out_s,
			cb1._B_t.in_s,
			cb2._B_t.in_s };

	class entry_point : public action {
	public:
		pss_ctor(entry_point, action);

	};
	pss_type(entry_point);

};
pss_type(static_structure);



