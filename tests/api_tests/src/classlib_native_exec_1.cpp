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

	methods_pkg(Type *p=0, psi_name name="methods_pkg") : Package(p, name) { }

	Import my_func { this, "my_func",
		(Bit<7,0>("a"), Bit<31,0>("b"))};

	Import my_func2 { this, "my_func2", Bit<7,0>(""),
		(Bit<7,0>("a"), Bit<31,0>("b"))};

} methods_pkgT;

class top : public Component {
public:
	TypeRgy<top>			type_id {this};

	top(Type *p=0, psi_name name="top") : Component(p, name) { }


	class entry_point : public Action {
	public:
		entry_point(Type *p=0, psi_name name="entry_point") : Action(p, name) { }

		Rand<Bit<7,0>>			p1 {this,"p1"};
		Rand<Bit<31,0>>			p2 {this,"p2"};
		Rand<Bit<31,0>>			p3 {this,"p3"};

		Exec pre_solve {this, Exec::PreSolve,
			{
					psi_typeid(methods_pkg).my_func((p1, p2)),
					psi_typeid(methods_pkg).my_func((p1+1, p2+4)) /*,
					p3 = methods_pkgT.my_func((p1+1, p2+4)),
					p2 != 5
					 */
			}
		};

		Exec post_solve {this, Exec::PostSolve,
			{
					p3 != 10,
					p2 == 5
			}
		};


	} entry_pointT {this};

} topT;


