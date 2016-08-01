/*
 * graph_select_test.h
 *
 *  Created on: May 5, 2016
 *      Author: ballance
 */

#include "../../../include/psi.h"

using namespace psi;

class top_c : public Component {
public:
	psi_ctor(top_c, Component);

	class A1 : public Action {
	public:
		psi_ctor(A1, Action);

	};
	psi_type(A1);

	class graph_select_test : public Action {
	public:
		psi_ctor(graph_select_test, Action);

		Field<A1>			psi_field(a1_1);
		Field<A1>			psi_field(a1_2);
		Field<A1>			psi_field(a1_3);
		Field<A1>			psi_field(a1_4);

		Graph graph {this, {
				Select {
						Sequential{a1_1, a1_2},
						Sequential{a1_3, a1_4}
				},
				Parallel {
						Sequential{a1_1, a1_2},
						Sequential{a1_3, a1_4}
				}
		}
		};
	};
	psi_type(graph_select_test);

};
psi_global_type(top_c);

