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

	class power_transition : public Action {
	public:
		psi_ctor(power_transition, Action);

		Rand<Int<31,0>>				psi_field(step);
		Input<power_state_s>		psi_field(prev);
		Output<power_state_s>		psi_field(next);

		Constraint step_c {this, {step == -1 || step == 1}};

		Constraint A_c {this, "A_c", { next.dmn_A == prev.dmn_A }};
		Constraint B_c {this, "B_c", { next.dmn_B == prev.dmn_B }};
		Constraint C_c {this, "C_c", { next.dmn_C == prev.dmn_C }};

	};
	psi_type(power_transition);

	class A_transition : public power_transition {
	public:
		psi_ctor(A_transition, power_transition);

		Constraint A_c {this, "A_c", {next.dmn_A == prev.dmn_A + step}};
	};
	psi_type(A_transition);

	class B_transition : public power_transition {
	public:
		psi_ctor(B_transition, power_transition);

		Constraint B_c {this, "B_c", {next.dmn_B == prev.dmn_B + step}};
	};
	psi_type(B_transition);

	class C_transition : public power_transition {
	public:
		psi_ctor(C_transition, power_transition);

		Constraint C_c {this, "C_c", {next.dmn_C == prev.dmn_C + step}};
	};
	psi_type(C_transition);

};
psi_global_type(my_system_c);



