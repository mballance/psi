/*
 * classlib_dac_tutorial_power_states_1.cpp
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

class power_state_s : public StateStruct {
public:
	pss_ctor(power_state_s, StateStruct);

	Rand<Bit<1,0>>		pss_field(dmn_A);
	Rand<Bit<1,0>>		pss_field(dmn_B);
	Rand<Bit<1,0>>		pss_field(dmn_C);

	Constraint c {this, {
			If {dmn_C != 0, dmn_B == 0},

			If {initial == 1, {
				dmn_A == 0,
				dmn_B == 0,
				dmn_C == 0
				}
			}
		}
	};
};
pss_global_type(power_state_s);

class my_system_c : public Component {
public:
	pss_ctor(my_system_c, Component);

	Field<power_state_s>		pss_field(ps);

};
pss_global_type(my_system_c);



