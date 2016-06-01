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
	TypeRgy<top_c>			type_id {this};

	top_c(Type *p=0, const std::string &name="top_c") : Component(p, name) { }

	class A1 : public Action {
	public:
		TypeRgy<A1>			type_id {this};
		A1(Type *p=0, const std::string &name="A1") : Action(p, name) { }

	} A1T {this};

	class graph_select_test : public Action {
	public:
		TypeRgy<graph_select_test>		type_id {this};

		graph_select_test(Type *p=0, const std::string &name="graph_select_test") : Action(p, name) { }

		Field<A1>			a1_1 {this, "a1_1"};
		Field<A1>			a1_2 {this, "a1_2"};
		Field<A1>			a1_3 {this, "a1_3"};
		Field<A1>			a1_4 {this, "a1_4"};

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
	} graph_select_testT {this};

} top_cT;

