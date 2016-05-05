/*
 * graph_select_test.h
 *
 *  Created on: May 5, 2016
 *      Author: ballance
 */

#include "psi.h"

using namespace psi;

class top_c : public Component {

public:
	top_c(const std::string &name="top_c", Type *p=0) : Component(name, p) { }

	class A1 : public Action {
	public:
		A1(const std::string &name="A1", Type *p=0) : Action(name, p) { }

	} A1T {"A1", this};

	class graph_select_test : public Action {
	public:
		graph_select_test(const std::string &name="graph_select_test", Type *p=0) : Action(name, p) { }

		Field<A1>			a1_1 {"a1_1", this, "A1"};
		Field<A1>			a1_2 {"a1_2", this, "A1"};
		Field<A1>			a1_3 {"a1_3", this, "A1"};
		Field<A1>			a1_4 {"a1_4", this, "A1"};

		Graph graph {this,
			(
				Select {
					(
						(a1_1,
						 a1_2),
						(a1_3,
						 a1_4)
					)
				},
				Parallel {
					(
						(a1_1, a1_2),
						(a1_3, a1_4)
					)
				}
			)
		};
	} graph_select_testT { "graph_select_test", this };

} top_cT;

