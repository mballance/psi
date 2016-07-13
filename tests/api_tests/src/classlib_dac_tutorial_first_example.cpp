/*
 * classlib_dac_tutorial_first_example.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

class C : public Component {
public:
	psi_ctor(C, Component);

	class A : public Action {
	public:
		psi_ctor(A, Action);
	};
	psi_type(A);

};
psi_global_type(C);


class static_structure : public Component {
public:
	Field<C>		psi_field(c1);
	Field<C>		psi_field(c2);

	psi_ctor(static_structure, Component);

	class entry : public Action {
	public:
		Field<C::A>				psi_field(a1);
		Field<C::A>				psi_field(a2);

		psi_ctor(entry, Action);

		Graph g1 {this, {
			Repeat {
				a1, a2
			}
		}
		};

	};
	psi_type(entry);
};
psi_global_type(static_structure);




