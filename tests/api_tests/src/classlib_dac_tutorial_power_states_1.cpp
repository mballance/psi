/*
 * classlib_dac_tutorial_power_states_1.cpp
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



