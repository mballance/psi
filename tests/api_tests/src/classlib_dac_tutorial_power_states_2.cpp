/*
 * classlib_dac_tutorial_power_states_1.cpp
 *
 *  Created on: May 11, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

static class power_state_s : public StateStruct {
public:
	TypeRgy<power_state_s>		type_id {this};

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

} power_state_sT;


static class my_system_c : public Component {
public:
	TypeRgy<my_system_c>		type_id {this};

	my_system_c(Type *p=0, psi_name name="my_system_c")
		: Component(p, name) { }

	class power_transition : public Action {
	public:
		TypeRgy<power_transition>		type_id {this};

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

	} power_transitionT {this};

	class A_transition : public power_transition {
	public:
		TypeRgy<A_transition>		type_id {this};

		A_transition(
				Type 		*p=0,
				psi_name	name="A_transition",
				Action		*super=TypeRgy<power_transition>::type_id()) :
			power_transition(p, name, super) { }

		Constraint A_c {this, "A_c", {next.dmn_A == prev.dmn_A + step}};
	} A_transitionT {this};

	class B_transition : public power_transition {
	public:
		TypeRgy<B_transition>		type_id {this};

		B_transition(
				Type 				*p=0,
				const std::string 	&name="B_transition",
				Action				*super=TypeRgy<power_transition>::type_id()) :
			power_transition(p, name, super) { }

		Constraint B_c {this, "B_c", {next.dmn_B == prev.dmn_B + step}};
	} B_transitionT {this};

	class C_transition : public power_transition {
	public:
		TypeRgy<B_transition>		type_id {this};

		C_transition(
				Type				*p=0,
				const std::string 	&name="C_transition",
				Action				*super=TypeRgy<power_transition>::type_id()) :
			power_transition(p, name, super) { }

		Constraint C_c {this, "C_c", {next.dmn_C == prev.dmn_C + step}};
	} C_transitionT {this};

} my_system_cT;



