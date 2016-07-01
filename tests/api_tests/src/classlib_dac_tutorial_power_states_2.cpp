/*
 * classlib_dac_tutorial_power_states_1.cpp
 *
 *  Created on: May 11, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

class power_state_s : public StateStruct {
public:

	power_state_s(Type *p=0, psi_name name="power_state_s")
		: StateStruct(p, name) { }

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
TypeDecl<power_state_s>		power_state_sT;


class my_system_c : public Component {
public:

	my_system_c(Type *p=0, psi_name name="my_system_c")
		: Component(p, name) { }

	class power_transition : public Action {
	public:

		power_transition(
				Type 		*p=0,
				psi_name	name="power_transition",
				Action 		*super=0) : Action(p, name, super) { }

		Rand<Int<31,0>>				step {this, "step"};
		Input<power_state_s>		prev {this, "prev"};
		Output<power_state_s>		next {this, "next"};

		Constraint step_c {this, {step == -1 || step == 1}};

		Constraint A_c {this, "A_c", { next.dmn_A == prev.dmn_A }};
		Constraint B_c {this, "B_c", { next.dmn_B == prev.dmn_B }};
		Constraint C_c {this, "C_c", { next.dmn_C == prev.dmn_C }};

	};
	TypeDecl<power_transition> power_transitionT {this};

	class A_transition : public power_transition {
	public:

		A_transition(
				Type 		*p=0,
				psi_name	name="A_transition",
				Action		*super=TypeRgy<power_transition>::type_id()) :
			power_transition(p, name, super) { }

		Constraint A_c {this, "A_c", {next.dmn_A == prev.dmn_A + step}};
	};
	TypeDecl<A_transition> A_transitionT {this};

	class B_transition : public power_transition {
	public:
		TypeRgy<B_transition>		type_id {this};

		B_transition(
				Type 				*p=0,
				const std::string 	&name="B_transition",
				Action				*super=TypeRgy<power_transition>::type_id()) :
			power_transition(p, name, super) { }

		Constraint B_c {this, "B_c", {next.dmn_B == prev.dmn_B + step}};
	};
	TypeDecl<B_transition> B_transitionT {this};

	class C_transition : public power_transition {
	public:

		C_transition(
				Type				*p=0,
				const std::string 	&name="C_transition",
				Action				*super=TypeRgy<power_transition>::type_id()) :
			power_transition(p, name, super) { }

		Constraint C_c {this, "C_c", {next.dmn_C == prev.dmn_C + step}};
	};
	TypeDecl<C_transition> C_transitionT {this};

};
TypeDecl<my_system_c> my_system_cT;



