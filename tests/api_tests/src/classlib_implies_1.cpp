/*
 * classlib_implies_1.cpp
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
 *  Created on: Aug 16, 2016
 *      Author: ballance
 */
#include "pss_tests.h"


class my_struct : public Struct {
public:
	my_struct(const Scope &p) : Struct(this) { }

	Rand<Bit<31,0>>				addr {this, "addr"};
	Rand<Bit<31,0>>				data {this, "data"};

	Constraint c { this, "c",
		{
			(addr == 5).implies(data == 2),
			(addr == 7).implies(
					data >= 0 && data <= 7
					)
		}
	};
};
TypeDecl<my_struct>		_my_struct_t;



