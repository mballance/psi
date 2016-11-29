/*
 * constraint_ifelse_test.h
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

class constraint_ifelse_test : public Struct {
public:
	pss_struct_ctor(constraint_ifelse_test);

	Rand<Bit<>>			pss_field(control);
	Rand<Bit<31,1>>		pss_field(address);
	Rand<Bit<31,1>>		pss_field(data);

	Constraint c1 {this, "c1",
		If {(control == 1), address < 10}
	};

	Constraint c2 {this,
		If {
			(control == 1),
			{
				address < 10,
				data > 0 && data < 100
			}, /* else */ {
				address > 10,
				data > 10 && data < 1000
			}
		}
	};

	Constraint c3 {this,
		If {
			(control == 1), {
						address == 1
			}, /* else */ {
					If {
						(address == 20), {
							data == 10
						}, /* else */ {
							data == 50
						}
					}
			}
		}
	};

};
pss_global_type(constraint_ifelse_test);


