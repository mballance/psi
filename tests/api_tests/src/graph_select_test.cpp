/*
 * graph_select_test.h
 *
 *  Created on: May 5, 2016
 *      Author: ballance
 */

#include "pss_tests.h"

class top_c : public Component {
public:
	pss_ctor(top_c, Component);

	class A1 : public Action {
	public:
		pss_ctor(A1, Action);

	};
	pss_type(A1);

	class graph_select_test : public Action {
	public:
		pss_ctor(graph_select_test, Action);

		Field<A1>			pss_field(a1_1);
		Field<A1>			pss_field(a1_2);
		Field<A1>			pss_field(a1_3);
		Field<A1>			pss_field(a1_4);

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
	pss_type(graph_select_test);

};
pss_global_type(top_c);

