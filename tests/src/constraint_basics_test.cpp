/*
 * constraint_basics_test.h
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
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#include "pss_tests.h"

class constraint_basics_test : public pss_struct {
public:
	pss_struct_ctor(constraint_basics_test);

	rand_attr<uint32_t>			pss_field(address);

	constraint c0 {address >= 0x1000 }; // named constraint

	constraint c1 {address >= 0x1000 && address <= 0x1fff }; // anonymous constraint

	constraint c2 {
			address >= 0x1000 , // comma used as constraint-statement separator
			                    // comma-separated statements must be surrounded in parens or braces
			address <= 0x1fff
			};

};
pss_type(constraint_basics_test);

