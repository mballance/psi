/*
 * classlis_dac_tutorial_data_flow.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#include "psi_tests.h"

static class S : public Struct {
public:
	TypeRgy<S>			type_id {this};

	S(Type *p=0, psi_name &name="S") : Struct(p, name) { }

} St;

static class CA : public Component {
public:
	TypeRgy<CA>			type_id {this};

	CA(Type *p=0, psi_name name="CA") : Component(p, name) {
	}

	class A : public Action {
	public:
		TypeRgy<A>			type_id {this};

		A(Type *p=0, psi_name name="A") : Action(p, name) { }

		Output<S>			out_s {this, "out_s"};
	} At {this};

} CAt;

static class CB : public Component {
public:
	TypeRgy<CB>			type_id {this};

	CB(Type *p=0, psi_name name="CB") : Component(p, name) { }

	class B : public Action {
	public:
		TypeRgy<B>			type_id {this};
		B(Type *p=0, psi_name name="B") : Action(p, name) { }

		Input<S>			in_s {"in_s", this, St};

	} Bt {this };
} CBt;

static class static_structure : public Component {
public:
	TypeRgy<static_structure>	type_id {this};

	Field<CA>			ca1 {"ca1", this};
	Field<CA>			ca2 {"ca2", this};
	Field<CB>			cb1 {"cb1", this};
	Field<CB>			cb2 {"cb2", this};

	static_structure(Type *p, psi_name name="static_structure")
		: Component(p, name) {

	}

	Bind b2 { this, {
			ca1.At.out_s(),
			ca2.At.out_s(),
			cb1.Bt.in_s(),
			cb2.Bt.in_s()}
	};

	class entry_point : public Action {
	public:
		TypeRgy<entry_point>	type_id {this};
		entry_point(Type *p, psi_name name) : Action(p, name) { }

	} entry_pointT {"entry_point", this};

} static_structureT;



