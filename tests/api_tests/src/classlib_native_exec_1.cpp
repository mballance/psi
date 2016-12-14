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

class methods_pkg : public package {
public:
	pss_ctor(methods_pkg, package);

	import_func my_func { this, "my_func",
		(input<pss_bit<7,0>>("a"), input<pss_bit<31,0>>("b"))};

	import_func my_func2 { this, "my_func2", pss_bit<7,0>(""),
		(input<pss_bit<7,0>>("a"), input<pss_bit<31,0>>("b"))};

};
pss_global_type(methods_pkg);

class top : public component {
public:
	pss_ctor(top, component);

	class entry_point : public action {
	public:
		pss_ctor(entry_point, action);

		rand_attr<pss_bit<7,0>>		pss_field(p1);
		rand_attr<pss_bit<7,0>>		pss_field(p2);
		rand_attr<pss_bit<7,0>>		pss_field(p3);

		exec post_solve_en {this, exec::PostSolve,
			{
					pss_typeid(methods_pkg).my_func({p1, p2}),
					pss_typeid(methods_pkg).my_func({p1+1, p2+4})
			}
		};

	};
	pss_type(entry_point);

};
pss_global_type(top);


