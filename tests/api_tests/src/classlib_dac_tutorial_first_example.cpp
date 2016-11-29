/*
 * classlib_dac_tutorial_first_example.cpp
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
 *  Created on: May 10, 2016
 *      Author: ballance
 */
#include "pss_tests.h"

class C : public Component {
public:
	pss_ctor(C, Component);

	class A : public Action {
	public:
		pss_ctor(A, Action);

		Rand<Bit<3,0>>		pss_field(field1);
	};
	pss_type(A);

};
pss_global_type(C);


class static_structure : public Component {
	pss_ctor(static_structure, Component);

	Field<C>		pss_field(c1);
	Field<C>		pss_field(c2);

	class entry : public Action {
		pss_ctor(entry, Action);

		GraphNode<C::A>			pss_field(a1);
		GraphNode<C::A>			pss_field(a2);

		Graph g1 {this,
			Repeat {5, {
					a1, a2.with(a2.field1 < 2)
				}
			}
		};
	};
	pss_type(entry);
};
pss_global_type(static_structure);




