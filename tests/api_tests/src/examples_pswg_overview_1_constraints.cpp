/*
 * classlib_dac_tutorial_power_states_1.cpp
 *
 *  Created on: May 11, 2016
 *      Author: ballance
 */
#include "pss_tests.h"

class power_state_s : public StateStruct {
public:
	power_state_s(const Scope &p) : StateStruct(this) { }

	Rand<Bit<1,0>>		dmn_A{this, "dmn_A"};
	Rand<Bit<1,0>>		dmn_B{this, "dmn_B"};
	Rand<Bit<1,0>>		dmn_C{this, "dmn_C"};

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
TypeDecl<power_state_s>		_power_state_s_t;


class my_system_c : public Component {
public:

	my_system_c(const Scope &p) : Component(this) { }

	class power_transition : public Action {
	public:

		power_transition(const Scope &p) : Action(this) { }

		Rand<Int<31,0>>				step {this, "step"};
		Input<power_state_s>		prev {this, "prev"};
		Output<power_state_s>		next {this, "next"};

		Constraint step_c {this, "step_c", {step == -1 || step == 1}};

		Constraint A_c {this, "A_c", { next.dmn_A == prev.dmn_A }};
		Constraint B_c {this, "B_c", { next.dmn_B == prev.dmn_B }};
		Constraint C_c {this, "C_c", { next.dmn_C == prev.dmn_C }};

	};
	TypeDecl<power_transition> _power_transition_t{this};

	class A_transition : public power_transition {
	public:
		A_transition(const Scope &p) : power_transition(this) { }

		Constraint A_c {this, "A_c", {next.dmn_A == prev.dmn_A + step}};
	};
	TypeDecl<A_transition> _A_transition_t{this};

	class B_transition : public power_transition {
	public:
		pss_ctor(B_transition, power_transition);

		pss_constraint(B_c, {next.dmn_B == prev.dmn_B + step});
	};
	TypeDecl<B_transition> _B_transition_t{this};

	class C_transition : public power_transition {
	public:

		C_transition(const Scope &p) : power_transition(this) { }

		Constraint C_c {this, "C_c", {next.dmn_C == prev.dmn_C + step}};
	};
	TypeDecl<C_transition> _C_transition_t{this};

};
pss_global_type(my_system_c);




