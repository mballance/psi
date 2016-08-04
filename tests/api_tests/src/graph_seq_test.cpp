/*
 * graph_seq_test.cpp
 *
 *  Created on: May 2, 2016
 *      Author: ballance
 */

#include "pss_tests.h"

class graph_seq_comp : public Component {
public:
	pss_ctor(graph_seq_comp, Component);

	class A1 : public Action {
	public:
		pss_ctor(A1, Action);

	};
	pss_type(A1);

	class graph_seq_test : public Action {
	public:
		pss_ctor(graph_seq_test, Action);

		Field<A1> pss_field(a1);
		Field<A1> pss_field(a2);
		Field<A1> pss_field(a3);

		Graph graph {this, Sequential {
			a1, a2, a3
		}
		};

	};
	pss_type(graph_seq_test);

};
pss_global_type(graph_seq_comp);




