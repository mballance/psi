/*
 * classlib_dac_tutorial_resources.cpp
 *
 *  Created on: May 11, 2016
 *      Author: ballance
 */
#include "psi_tests.h"


static class R : public ResourceStruct {
public:
	R(const std::string &name="R", Type *p=0) : ResourceStruct(name, p) { }

} Rt;

static class C : public Component {
public:
	C(const std::string &name="C", Type *p=0) : Component(name, p) { }

	class A : public Action {
	public:
		A(const std::string &name, Type *p) : Action(name, p) { }

		Lock<R>			rc {"rc", this, Rt};

	} At {"A", this};

} Ct;

static class static_structure : public Component {
public:
	static_structure(const std::string &name="static_structure", Type *p=0)
		: Component(name, p) { }

	Field<C>			c1 {"c1", this, Ct};
	Field<C>			c2 {"c2", this, Ct};

	Pool<R>				rp {"rp", this, Rt};

	// Bind rp, c1.A, c2.A
	Bind b {this, {rp(), c1(), c2()}};

} static_structureT;

static class top : public Component {
public:

	top(const std::string &name="top", Type *p=0) : Component(name, p) { }

	class entry_point : public Action {
	public:
		entry_point(const std::string &name, Type *p) : Action(name, p) { }

		C::A			a1 {"a1", this};
		C::A			a2 {"a2", this};

		Graph graph {this,
			Parallel {
				(a1, a2)
			}
		};
	};

} topT;




