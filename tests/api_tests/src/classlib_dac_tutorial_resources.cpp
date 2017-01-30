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


class R : public resource_struct {
public:
	pss_ctor(R, resource_struct);

};
pss_type(R);

class C : public component {
public:
	pss_ctor(C, component);

	class A : public action {
	public:
		pss_ctor(A, action);

		lock<R>			pss_field(rc);
	};
	pss_type(A);
};
pss_type(C);

class static_structure : public component {
public:
	pss_ctor(static_structure, component);

	C					pss_field(c1);
	C					pss_field(c2);

	pool<R>				pss_field(rp);

	bind b1 {this, rp, c1};
	bind b2 {this, rp, c2};

	bind b {this, rp, c1, c2};

};
pss_type(static_structure);

class top : public component {
public:
	pss_ctor(top, component);

	class entry_point : public action {
	public:
		pss_ctor(entry_point, action);

		C::A			pss_field(a1);
		C::A			pss_field(a2);

		activity g {this,
			parallel {
				a1, a2
			}
		};
	};
	pss_type(entry_point);

};
pss_type(top);




