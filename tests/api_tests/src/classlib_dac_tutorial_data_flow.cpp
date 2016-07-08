/*
 * classlis_dac_tutorial_data_flow.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#include "psi_tests.h"

class S : public Struct {
public:

	S(const Scope &p) : Struct(this) { }

};
psi_global_type(S);

class CA : public Component {
public:
	CA(const Scope &p) : Component(this) { }

	class A : public Action {
	public:
		A(const Scope &p) : Action(this) { }

		Output<S>			out_s {this, "out_s"};
	};
	psi_type(A);

};
psi_global_type(CA);

class CB : public Component {
public:
	CB(const Scope &p) : Component(this) { }

	class B : public Action {
	public:
		B(const Scope &p) : Action(this) { }

		Input<S>			in_s {this, "in_s"};
	};
	psi_type(B);
};
psi_global_type(CB);

class static_structure : public Component {
public:

	Field<CA>			ca1 {this, "ca1"};
	Field<CA>			ca2 {this, "ca2"};
	Field<CB>			cb1 {this, "cb1"};
	Field<CB>			cb2 {this, "cb2"};

	static_structure(const Scope &p) : Component(this) { }

	// TODO:
	Bind b2 { this,
			ca1._A_t.out_s, ca2._A_t.out_s,
			cb1._B_t.in_s, cb2._B_t.in_s };

	class entry_point : public Action {
	public:
		entry_point(const Scope &p) : Action(this) { }

	};
	psi_type(entry_point);

};
psi_global_type(static_structure);



