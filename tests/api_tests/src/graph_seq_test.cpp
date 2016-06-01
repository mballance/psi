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
	TypeRgy<graph_seq_comp>		type_id {this};

	graph_seq_comp(Type *p=0, const std::string &name="graph_seq_comp") :
		Component(p, name) { }

	class A1 : public Action {
	public:
		TypeRgy<A1>		type_id {this};
		A1(Type *p=0, const std::string &name="A1") : Action(p, name) { }

	} A1T {this};

	class graph_seq_test : public Action {
	public:
		TypeRgy<graph_seq_test>		type_id {this};

		graph_seq_test(Type *p=0, const std::string &name="graph_seq_test") : Action(p, name) { }

		Field<A1> a1{this, "a1"};
		Field<A1> a2{this, "a2"};
		Field<A1> a3{this, "a3"};

		Graph graph {this,
			(a1, a2, a3)
		};

	} graph_seq_testT {this};

} graph_seq_compT;




