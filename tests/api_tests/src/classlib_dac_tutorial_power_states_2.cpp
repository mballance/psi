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

	class power_transition : public Action {
	public:

		pss_ctor(power_transition, Action);

		Rand<Int<31,0>>				pss_field(step);
		Input<power_state_s>		pss_field(prev);
		Output<power_state_s>		pss_field(next);

		pss_constraint(step_c, {step == -1 || step == 1});

		pss_constraint(A_c, { next.dmn_A == prev.dmn_A });
		pss_constraint(B_c, { next.dmn_B == prev.dmn_B });
		pss_constraint(C_c, { next.dmn_C == prev.dmn_C });

	};
	pss_type(power_transition);

	class A_transition : public power_transition {
	public:
		pss_ctor(A_transition, power_transition);

		pss_constraint(A_c, {next.dmn_A == prev.dmn_A + step});
	};
	pss_type(A_transition);

	class B_transition : public power_transition {
	public:
		pss_ctor(B_transition, power_transition);

		pss_constraint(B_c, {next.dmn_B == prev.dmn_B + step});
	};
	pss_type(B_transition);

	class C_transition : public power_transition {
	public:

		pss_ctor(C_transition, power_transition);

		pss_constraint(C_c, {next.dmn_C == prev.dmn_C + step});
	};
	pss_type(C_transition);

};
pss_global_type(my_system_c);




