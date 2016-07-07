/*
 * classlib_native_exec_1.cpp
 *
 *  Created on: May 11, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

static class methods_pkg : public Package {
public:
	TypeRgy<methods_pkg>		type_id {this};

	methods_pkg(BaseItem *p=0, psi_name name="methods_pkg") : Package(p, name) { }

	Import my_func {this, "my_func",
		(Bit<7,0>("a"), Bit<31,0>("b"))};

	Import my_func2 {this, "my_func2", Bit<7,0>(""),
		(Bit<7,0>("a"), Bit<31,0>("b"))};

} methods_pkgT;

class top : public Component {
public:
	TypeRgy<top>			type_id {this};

	top(BaseItem *p=0, psi_name name="top") : Component(p, name) { }


	class entry_point : public Action {
	public:
		TypeRgy<entry_point>		type_id {this};

		entry_point(BaseItem *p=0, psi_name name="entry_point") : Action(p, name) { }

		Rand<Bit<7,0>>			p1 {this, "p1"};
		Rand<Bit<31,0>>			p2 {this, "p2"};
		Rand<Bit<31,0>>			p3 {this, "p3"};
		Bit<31,0>				p4 {this, "p4"};
		Bit<31,0>				p5 {this, "p5"};

		Exec pre_solve_e {this, Exec::PreSolve, { p4() } };

		Exec post_solve_e {this, Exec::PostSolve, { p5() } };

		void pre_solve() {
			// TODO: set p4
		}

		void post_solve() {
			// TODO: set p5
		}


	} entry_pointT {this};

} topT;


