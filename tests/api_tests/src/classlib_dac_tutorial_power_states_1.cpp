/*
 * classlib_dac_tutorial_power_states_1.cpp
 *
 *  Created on: May 11, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

class power_state_s : public StateStruct {
public:
	psi_ctor(power_state_s, StateStruct);

	Rand<Bit<1,0>>		psi_field(dmn_A);
	Rand<Bit<1,0>>		psi_field(dmn_B);
	Rand<Bit<1,0>>		psi_field(dmn_C);

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
psi_global_type(power_state_s);

class my_system_c : public Component {
public:
	psi_ctor(my_system_c, Component);

	Field<power_state_s>		psi_field(ps);

};
psi_global_type(my_system_c);



