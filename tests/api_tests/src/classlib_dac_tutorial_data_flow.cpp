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

class S : public Struct {
public:
	pss_ctor(S, Struct);

};
pss_global_type(S);

class CA : public Component {
public:
	pss_ctor(CA, Component);

	class A : public Action {
	public:
		pss_ctor(A, Action);

		Output<S>			pss_field(out_s);
	};
	pss_type(A);

};
pss_global_type(CA);

class CB : public Component {
public:
	pss_ctor(CB, Component);

	class B : public Action {
	public:
		pss_ctor(B, Action);

		Input<S>			pss_field(in_s);
	};
	pss_type(B);
};
pss_global_type(CB);

class static_structure : public Component {
public:

	Field<CA>			pss_field(ca1);
	Field<CA>			pss_field(ca2);
	Field<CB>			pss_field(cb1);
	Field<CB>			pss_field(cb2);

	pss_ctor(static_structure, Component);

	// TODO:
	Bind b2 { this,
			// ca1.A.out_s
			ca1._A_t.out_s,
			ca2._A_t.out_s,
			cb1._B_t.in_s,
			cb2._B_t.in_s };

	class entry_point : public Action {
	public:
		pss_ctor(entry_point, Action);

	};
	pss_type(entry_point);

};
pss_global_type(static_structure);



