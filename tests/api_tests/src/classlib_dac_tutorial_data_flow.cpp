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
	S(const Scope &s) : pss_struct(this) { }

};
type_decl<S> _S_t;

class CA : public component {
public:
	CA(const Scope &s) : component(this) { }

	class A : public action {
	public:
		A(const Scope &s) : action(this) { }

		output<S>			out_s {"out_s"};
	};
	type_decl<A> _A_t;

};
type_decl<CA> _CA_t;

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
	type_decl<entry_point> _type_decl_t;

};
pss_type(static_structure);



