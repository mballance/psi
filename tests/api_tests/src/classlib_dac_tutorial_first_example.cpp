/*
 * classlib_dac_tutorial_first_example.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */
#include "pss_tests.h"

class C : public Component {
public:
	pss_ctor(C, Component);

	class A : public Action {
	public:
		pss_ctor(A, Action);

		Rand<Bit<3,0>>		pss_field(field1);
	};
	pss_type(A);

};
pss_global_type(C);


class static_structure : public Component {
	pss_ctor(static_structure, Component);

	Field<C>		pss_field(c1);
	Field<C>		pss_field(c2);

	class entry : public Action {
		pss_ctor(entry, Action);

		Field<C::A>				pss_field(a1);
		Field<C::A>				pss_field(a2);

		Graph g1 {this, {
			Repeat {5, {
					a1, a2.with(a2.field1 < 2)
				}
			}
		}
		};
	};
	pss_type(entry);
};
pss_global_type(static_structure);




