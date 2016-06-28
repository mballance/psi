/*
 * classlib_dac_tutorial_first_example.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

static class C : public Component {
public:
	TypeRgy<C>		type_id {this};

	C(Type *p=0, psi_name name="C") : Component(p, name)  { }

	class A : public Action {
	public:
		A(Type *p=0, psi_name name="A") : Action(p, name) { }
	} At {this};

} Ct;


class static_structure : public Component {
public:
	TypeRgy<static_structure>		type_id{this};

	Field<C>		c1 {this, "c1"};
	Field<C>		c2 {this, "c2"};

	static_structure(
			Type				*p=0,
			const std::string 	&name="static_structure") : Component(p, name) { }

	class entry : public Action {
	public:
		TypeRgy<entry>			type_id{this};

		Field<C::A>				a1 {this, "a1"};
		Field<C::A>				a2 {this, "a2"};

		entry(Type *p=0, psi_name name="entry") : Action(p, name) { }

		Graph g1 {this, {
			Repeat {
				a1, a2
			}
		}
		};

	} entryT {this};

} static_structureT;




