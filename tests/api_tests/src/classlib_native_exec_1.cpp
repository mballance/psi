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

class methods_pkg : public Package {
public:
	pss_ctor(methods_pkg, Package);

	ImportFunc my_func { this, "my_func",
		(Input<Bit<7,0>>("a"), Input<Bit<31,0>>("b"))};

	ImportFunc my_func2 { this, "my_func2", Bit<7,0>(""),
		(Input<Bit<7,0>>("a"), Input<Bit<31,0>>("b"))};

};
pss_global_type(methods_pkg);

class top : public Component {
public:
	pss_ctor(top, Component);

	class entry_point : public Action {
	public:
		pss_ctor(entry_point, Action);

		Rand<Bit<7,0>>		pss_field(p1);
		Rand<Bit<7,0>>		pss_field(p2);
		Rand<Bit<7,0>>		pss_field(p3);

		Exec post_solve_en {this, Exec::PostSolve,
			{
					pss_typeid(methods_pkg).my_func({p1, p2}),
					pss_typeid(methods_pkg).my_func({p1+1, p2+4})
			}
		};

	};
	pss_type(entry_point);

};
pss_global_type(top);


