/*
 * classlib_native_exec_1.cpp
 *
 *  Created on: May 11, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

class methods_pkg : public Package {
public:
	psi_ctor(methods_pkg, Package);

	Import my_func { this, "my_func",
		(Bit<7,0>("a"), Bit<31,0>("b"))};

	Import my_func2 { this, "my_func2", Bit<7,0>(""),
		(Bit<7,0>("a"), Bit<31,0>("b"))};

};
psi_global_type(methods_pkg);

class top : public Component {
public:
	psi_ctor(top, Component);

	class entry_point : public Action {
	public:
		psi_ctor(entry_point, Action);

		Rand<Bit<7,0>>		psi_field(p1);
		Rand<Bit<7,0>>		psi_field(p2);
		Rand<Bit<7,0>>		psi_field(p3);

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


	};
	psi_type(entry_point);

};
psi_global_type(top);


