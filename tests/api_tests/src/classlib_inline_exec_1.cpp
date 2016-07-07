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

class methods_pkg : public Package {
public:
	methods_pkg(BaseItem *p=0, psi_name name="methods_pkg") : Package(p, name) { }

	Import my_func {this, "my_func",
		(Bit<7,0>("a"), Bit<31,0>("b"))};

	Import my_func2 {this, "my_func2", Bit<7,0>(""),
		(Bit<7,0>("a"), Bit<31,0>("b"))};

};
TypeDecl<methods_pkg> methods_pkgT;

class top : public Component {
public:
	top(BaseItem *p=0, psi_name name="top") : Component(p, name) { }


	class entry_point : public Action {
	public:
		entry_point(BaseItem *p=0, psi_name name="entry_point") : Action(p, name) { }

		Rand<Bit<7,0>>			p1 {this, "p1"};
		Rand<Bit<31,0>>			p2 {this, "p2"};
		Rand<Bit<31,0>>			p3 {this, "p3"};
		Bit<31,0>				p4 {this, "p4"};
		Bit<31,0>				p5 {this, "p5"};

		Exec pre_solve_e {this, Exec::PreSolve, { p4 } };

		Exec post_solve_e {this, Exec::PostSolve, { p5 } };

		void pre_solve() {
			// Set p4 based on calling a generation-time method
			p4.set(refmodel_get_next_value());
		}

		void post_solve() {
			// Set p5 based on a calculated value
			p4.set(p1.get() + p2.get());
		}
	};
	TypeDecl<entry_point> entry_pointT {this};

};
TypeDecl<top> topT;


