/*
 * classlib_dac_tutorial_first_example.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */
#include "psi_tests.h"

class C : public Component {
public:
	C(const Scope &p) : Component(p)  { }

	class A : public Action {
	public:
		A(const Scope &p) : Action(p) { }
	};
	TypeDecl<A> At {this};

};
TypeDecl<C> Ct;


class static_structure : public Component {
public:
	Field<C>		c1 {this, "c1"};
	Field<C>		c2 {this, "c2"};

	static_structure(const Scope &p) : Component(p) { }

	class entry : public Action {
	public:
		Field<C::A>				a1 {this, "a1"};
		Field<C::A>				a2 {this, "a2"};

		entry(const Scope &p) : Action(p) { }

		Graph g1 {this, {
			Repeat {
				a1, a2
			}
		}
		};

	};
	TypeDecl<entry> entryT {this};

};
TypeDecl<static_structure> static_structureT;




