/*
 * classlib_dac_tutorial_resources.cpp
 *
 *  Created on: May 11, 2016
 *      Author: ballance
 */
#include "psi_tests.h"


class R : public ResourceStruct {
public:
	psi_ctor(R, ResourceStruct);

};
psi_global_type(R);

class C : public Component {
public:
	psi_ctor(C, Component);

	class A : public Action {
	public:
		psi_ctor(A, Action);

		Lock<R>			psi_field(rc);
	};
	psi_type(A);
};
psi_global_type(C);

class static_structure : public Component {
public:
	psi_ctor(static_structure, Component);

	Field<C>			psi_field(c1);
	Field<C>			psi_field(c2);

	Pool<R>				psi_field(rp);

	Bind b1 {this, rp, c1};
	Bind b2 {this, rp, c2};

	Bind b {this, rp, c1, c2};

};
psi_global_type(static_structure);

class top : public Component {
public:
	psi_ctor(top, Component);

	class entry_point : public Action {
	public:
		psi_ctor(entry_point, Action);

		Field<C::A>			psi_field(a1);
		Field<C::A>			psi_field(a2);

		Graph graph {this,
			Parallel {
				a1, a2
			}
		};
	};
	psi_type(entry_point);

};
psi_global_type(top);




