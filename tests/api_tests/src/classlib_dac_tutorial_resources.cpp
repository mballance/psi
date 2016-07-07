/*
 * classlib_dac_tutorial_resources.cpp
 *
 *  Created on: May 11, 2016
 *      Author: ballance
 */
#include "psi_tests.h"


class R : public ResourceStruct {
public:
	R(BaseItem *p=0, psi_name name="R") : ResourceStruct(p, name) { }

};
TypeDecl<R> Rt;

class C : public Component {
public:
	C(BaseItem *p=0, psi_name name="C") : Component(p, name) { }

	class A : public Action {
	public:
		A(BaseItem *p=0, psi_name name="A") : Action(p, name) { }

		Lock<R>			rc {this, "rc"};
	};
	TypeDecl<A> At {this};

};
TypeDecl<C> Ct;

class static_structure : public Component {
public:
	static_structure(BaseItem *p=0, psi_name name="static_structure")
		: Component(p, name) { }

	Field<C>			c1 {this, "c1"};
	Field<C>			c2 {this, "c2"};

	Pool<R>				rp {this, "rp"};

	Bind b1 {this, rp, c1};
	Bind b2 {this, rp, c2};

	Bind b {this, {rp(), c1(), c2()}};

};
TypeDecl<static_structure> static_structureT;

class top : public Component {
public:
	top(psi_name name="top", BaseItem *p=0) : Component(p, name) { }

	class entry_point : public Action {
	public:
		entry_point(BaseItem *p=0, psi_name name="entry_point") : Action(p, name) { }

		Field<C::A>			a1 {this, "a1"};
		Field<C::A>			a2 {this, "a2"};

		Graph graph {this,
			Parallel {
				(a1, a2)
			}
		};
	};
	TypeDecl<entry_point> entry_pointT {this};

};
TypeDecl<top> topT;




