/*
 * graph_seq_test.cpp
 *
 *  Created on: May 2, 2016
 *      Author: ballance
 */

#include "psi.h"

using namespace psi;

class graph_seq_comp : public Component {
public:
	psi_ctor(graph_seq_comp, Component);

	class A1 : public Action {
	public:
		psi_ctor(A1, Action);

	};
	psi_type(A1);

	class graph_seq_test : public Action {
	public:
		psi_ctor(graph_seq_test, Action);

		Field<A1> psi_field(a1);
		Field<A1> psi_field(a2);
		Field<A1> psi_field(a3);

		Graph graph {this, Sequential {
			a1, a2, a3
		}
		};

	};
	psi_type(graph_seq_test);

};
psi_global_type(graph_seq_comp);




