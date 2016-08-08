/*
 * classlib_dac_tutorial_resources.cpp
 *
 *  Created on: May 11, 2016
 *      Author: ballance
 */
#include "pss_tests.h"


class R : public ResourceStruct {
public:
	pss_ctor(R, ResourceStruct);

};
pss_global_type(R);

class C : public Component {
public:
	pss_ctor(C, Component);

	class A : public Action {
	public:
		pss_ctor(A, Action);

		Lock<R>			pss_field(rc);
	};
	pss_type(A);
};
pss_global_type(C);

class static_structure : public Component {
public:
	pss_ctor(static_structure, Component);

	Field<C>			pss_field(c1);
	Field<C>			pss_field(c2);

	Pool<R>				pss_field(rp);

	Bind b1 {this, rp, c1};
	Bind b2 {this, rp, c2};

	Bind b {this, rp, c1, c2};

};
pss_global_type(static_structure);

class top : public Component {
public:
	pss_ctor(top, Component);

	class entry_point : public Action {
	public:
		pss_ctor(entry_point, Action);

		Field<C::A>			pss_field(a1);
		Field<C::A>			pss_field(a2);

		Graph graph {this,
			Parallel {
				a1, a2
			}
		};
	};
	pss_type(entry_point);

};
pss_global_type(top);




