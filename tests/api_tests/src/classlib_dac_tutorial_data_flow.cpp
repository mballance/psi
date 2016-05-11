/*
 * classlis_dac_tutorial_data_flow.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#include "psi_tests.h"

static class S : public Struct {
public:
	S(const std::string &name="S", Type *p=0) : Struct(name, p) { }

} St;

static class CA : public Component {
public:
	CA(const std::string &name="CA", Type *p=0) : Component(name, p) {
	}

	class A : public Action {
	public:
		A(const std::string &name="A", Type *p=0) : Action(name, p) { }

		Output<S>			out_s {"out_s", this, St};
	} At { "A", this };

} CAt;

static class CB : public Component {
public:
	CB(const std::string &name="CB", Type *p=0) : Component(name, p) { }

	class B : public Action {
	public:
		B(const std::string &name, Type *p) : Action(name, p) { }

		Input<S>			in_s {"in_s", this, St};

	} Bt { "B", this };
} CBt;

static class static_structure : public Component {
public:
	Field<CA>			ca1 {"ca1", this, CAt};
	Field<CA>			ca2 {"ca2", this, CAt};
	Field<CB>			cb1 {"cb1", this, CBt};
	Field<CB>			cb2 {"cb2", this, CBt};

	static_structure(const std::string &name="static_structure", Type *p=0)
		: Component(name, p) {

	}

	Bind b2 { this, {
			ca1.At.out_s(),
			ca2.At.out_s(),
			cb1.Bt.in_s(),
			cb2.Bt.in_s()}
	};

	class entry_point : public Action {
	public:
		entry_point(const std::string &name, Type *p) : Action(name, p) { }

	} entry_pointT {"entry_point", this};

} static_structureT;



