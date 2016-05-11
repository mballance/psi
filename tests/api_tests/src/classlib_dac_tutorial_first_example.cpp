/*
 * classlib_dac_tutorial_first_example.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

static class C : public Component {
public:

	C(const std::string &name="C", Type *p=0) : Component(name, p)  { }

	class A : public Action {
	public:
		A(const std::string &name, Type *p) : Action(name, p) { }
	} At {"A", this};

} Ct;


class static_structure : public Component {
public:
	Field<C>		c1 { "c1",  this, Ct };
	Field<C>		c2 { "c2",  this, Ct };

	static_structure(
			const std::string 	&name="static_structure",
			Type 				*p=0) : Component(name, p) { }

	class entry : public Action {
	public:
		Field<C::A>				a1 {"a1", this, Ct.At};
		Field<C::A>				a2 {"a2", this, Ct.At};

		entry(const std::string &name, Type *p) : Action(name, p) { }

		Graph g1 {this, Repeat {
			a1, a2
		}};

	} entryT {"entry", this};

} static_structureT;




