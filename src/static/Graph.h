/*
 * Graph.h
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include "Type.h"
#include "GraphStmtSeq.h"

namespace psi {

class Graph {

	public:
		Graph(Type *p, const ParamList &seq);

		virtual ~Graph();

	private:
//		GraphStmtSeq			m_seq;
};

} /* namespace psi */

#endif /* GRAPH_H_ */
