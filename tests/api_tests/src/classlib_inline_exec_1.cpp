/*
 * classlib_native_exec_1.cpp
 *
 *  Created on: May 11, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

int refmodel_get_next_value() {
	return 27;
}

class top : public Component {
public:
	psi_component_ctor(top);

	class entry_point : public Action {
	public:
		psi_action_ctor(entry_point);

		Rand<Bit<7,0>>		psi_field(p1);
		Rand<Bit<31,0>>		psi_field(p2);
		Rand<Bit<31,0>>		psi_field(p3);
		Field<Bit<31,0>>	psi_field(p4);
		Field<Bit<31,0>>	psi_field(p5);

		Exec pre_solve_e {this, Exec::PreSolve};

		Exec post_solve_e {this, Exec::PostSolve};

		void pre_solve() {
			// Set p4 based on calling a generation-time method
			p4.set(refmodel_get_next_value());
		}

		void post_solve() {
			// Set p5 based on a calculated value
			p5.set(p1.get() + p2.get());
		}
	};
	psi_type(entry_point);

};
psi_global_type(top);


