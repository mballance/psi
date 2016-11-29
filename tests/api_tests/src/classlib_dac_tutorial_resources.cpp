/*
 * classlib_dac_tutorial_resources.cpp
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


class R : public ResourceStruct {
public:
	pss_ctor(R, ResourceStruct);

};
pss_global_type(R);

class C : public Component {
public:
	pss_ctor(C, Component);

	class A : public Action {
	public:
		pss_ctor(A, Action);

		Lock<R>			pss_field(rc);
	};
	pss_type(A);
};
pss_global_type(C);

class static_structure : public Component {
public:
	pss_ctor(static_structure, Component);

	Field<C>			pss_field(c1);
	Field<C>			pss_field(c2);

	Pool<R>				pss_field(rp);

	Bind b1 {this, rp, c1};
	Bind b2 {this, rp, c2};

	Bind b {this, rp, c1, c2};

};
pss_global_type(static_structure);

class top : public Component {
public:
	pss_ctor(top, Component);

	class entry_point : public Action {
	public:
		pss_ctor(entry_point, Action);

		Field<C::A>			pss_field(a1);
		Field<C::A>			pss_field(a2);

		Graph graph {this,
			Parallel {
				a1, a2
			}
		};
	};
	pss_type(entry_point);

};
pss_global_type(top);




