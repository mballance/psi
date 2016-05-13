/*
 * classlib_dac_tutorial_resources.cpp
 *
 *  Created on: May 11, 2016
 *      Author: ballance
 */
#include "psi_tests.h"


static class R : public ResourceStruct {
public:
	TypeRgy<R>		type_id {this};

	R(Type *p=0, psi_name name="R") : ResourceStruct(p, name) { }

} Rt;

static class C : public Component {
public:
	TypeRgy<C>		type_id {this};

	C(psi_name name="C", Type *p=0) : Component(p, name) { }

	class A : public Action {
	public:
		A(Type *p=0, psi_name name="A") : Action(p, name) { }

		Lock<R>			rc {this, "rc"};

	} At {this};

} Ct;

static class static_structure : public Component {
public:
	TypeRgy<static_structure>		type_id {this};

	static_structure(Type *p=0, psi_name name="static_structure")
		: Component(p, name) { }

	Field<C>			c1 {this, "c1"};
	Field<C>			c2 {this, "c2"};

	Pool<R>				rp {this, "rp"};

	// Bind rp, c1.A, c2.A
	Bind b {this, {rp(), c1(), c2()}};

} static_structureT;

static class top : public Component {
public:
	TypeRgy<top>		type_id {this};

	top(psi_name name="top", Type *p=0) : Component(p, name) { }

	class entry_point : public Action {
	public:
		TypeRgy<entry_point>		type_id {this};

		entry_point(Type *p=0, psi_name name="entry_point") : Action(p, name) { }

		C::A			a1 {this, "a1"};
		C::A			a2 {this, "a2"};

		Graph graph {this,
			Parallel {
				(a1, a2)
			}
		};
	} entry_pointT {this};

} topT;




