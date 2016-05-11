/*
 * classlib_native_exec_1.cpp
 *
 *  Created on: May 11, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

static class methods_pkg : public Package {
public:
	methods_pkg(const std::string &name="methods_pkg", Type *p=0) : Package(name, p) { }

	Import my_func { "my_func", this,
		(Bit<7,0>("a"), Bit<31,0>("b"))};

	Import my_func2 { "my_func2", this, Bit<7,0>(""),
		(Bit<7,0>("a"), Bit<31,0>("b"))};

} methods_pkgT;

class top : public Component {
public:

	top(const std::string &name="top", Type *p=0) : Component(name, p) { }


	class entry_point : public Action {
	public:
		entry_point(const std::string &name, Type *p) : Action(name, p) { }

		Rand<Bit<7,0>>			p1 {"p1",this};
		Rand<Bit<31,0>>			p2 {"p2",this};
		Rand<Bit<31,0>>			p3 {"p3",this};
		Bit<31,0>				p4 {"p4",this};
		Bit<31,0>				p5 {"p5",this};

		Exec pre_solve_e {Exec::PreSolve, this,
			mk_exec(this, pre_solve),
			{ p4() }
		};

		Exec post_solve_e {Exec::PostSolve, this,
			mk_exec(this, post_solve),
			{ p5() }
		};

		void pre_solve() {
			// TODO: set p4
		}

		void post_solve() {
			// TODO: set p5
		}


	} entry_pointT {"entry_point", this};

} topT;


