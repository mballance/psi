/*
 * Graph.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "classlib/Graph.h"

namespace psi {

Graph::Graph(Type *p, const ExprList &seq) :
		Type(Type::TypeGraph, p), m_seq(seq) { }

Graph::~Graph() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
