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

		Rand<Bit<3,0>>		psi_field(field1);
	};
	psi_type(A);

};
psi_global_type(C);


class static_structure : public Component {
	psi_ctor(static_structure, Component);

	Field<C>		psi_field(c1);
	Field<C>		psi_field(c2);

	class entry : public Action {
		psi_ctor(entry, Action);

		Field<C::A>				psi_field(a1);
		Field<C::A>				psi_field(a2);

		Graph g1 {this, {
			Repeat {5, {
					a1, With { a2, {a2.field1 < 2} }
				}
			},
			Repeat {5, {
					a1, a2.with(a2.field1 < 2)
				}
			}
		}
		};
	};
	psi_type(entry);
};
psi_global_type(static_structure);




