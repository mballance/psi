/*
 * graph_seq_test.cpp
 *
 *  Created on: May 2, 2016
 *      Author: ballance
 */

#include "psi.h"

using namespace psi;

static class graph_seq_comp : public Component {

public:

	graph_seq_comp(const std::string &name="graph_seq_comp", Type *p = nullptr) :
		Component(name, p) { }

	class A1 : public Action {
	public:
		A1(const std::string &name, Type *p) : Action(name, p) { }

	} A1T { "A1", this };

	class graph_seq_test : public Action {
	public:

		graph_seq_test(const std::string &name, Type *p) : Action(name, p) { }

		Field<A1> a1{"a1", this, "A1"};
		Field<A1> a2{"a2", this, "A1"};
		Field<A1> a3{"a3", this, "A1"};

		Graph graph {this,
			(a1, a2, a3)
		};

	} graph_seq_testT { "graph_seq_test", this };

} graph_seq_compT;




