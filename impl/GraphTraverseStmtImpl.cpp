/*
 * GraphTraverseStmtImpl.cpp
 *
 *  Created on: Jun 10, 2016
 *      Author: ballance
 */

#include "GraphTraverseStmtImpl.h"

namespace psi {

GraphTraverseStmtImpl::GraphTraverseStmtImpl(IFieldRef *action, IConstraint *c) {
	m_action = action;
	m_constraint = c;
}

GraphTraverseStmtImpl::~GraphTraverseStmtImpl() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
