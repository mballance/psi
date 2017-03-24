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

class C : public component {
public:
	pss_ctor(C, component);

	class A : public action {
	public:
		pss_ctor(A, action);

		rand_attr<pss_bit>		field1 {"field1", {4}};
	};
	pss_type(A);

};
pss_type(C);


class static_structure : public component {
	pss_ctor(static_structure, component);

	C			c1{"c1"};
	C			c2{"c2"};

	class entry : public action {
		pss_ctor(entry, action);

		C::A			a1{"a1"};
		C::A			a2{"a2"};

		activity g1 {
			repeat {5, 
				a1, 
				a2.with(a2.field1 < 2)
			}
		};
	};
	pss_type(entry);
};
pss_type(static_structure);




