/*
 * classlib_dac_tutorial_power_states_1.cpp
 *
 *  Created on: May 11, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

class power_state_s : public StateStruct {
public:
	power_state_s(BaseItem *p=0, psi_name name="power_state_s") : StateStruct(p, name) { }

	Rand<Bit<1,0>>		dmn_A {this, "dmn_A"};
	Rand<Bit<1,0>>		dmn_B {this, "dmn_B"};
	Rand<Bit<1,0>>		dmn_C {this, "dmn_C"};

	Constraint c {this, {
			If {dmn_C != 0, dmn_B == 0},

			If {initial == 1, (
				dmn_A == 0,
				dmn_B == 0,
				dmn_C == 0
				)
			}
		}
	};
};
TypeDecl<power_state_s> power_state_sT;

class my_system_c : public Component {
public:
	my_system_c(BaseItem *p=0, psi_name name="my_system_c") : Component(p, name) { }

	Field<power_state_s>			ps {this, "ps"};

};
TypeDecl<my_system_c> my_system_cT;



