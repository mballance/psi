/*
 * GraphBlockStmtImpl.cpp
 *
 *  Created on: Jun 8, 2016
 *      Author: ballance
 */

#include "GraphBlockStmtImpl.h"

namespace psi {

GraphBlockStmtImpl::GraphBlockStmtImpl(IGraphBlockStmt::GraphStmtType type) : m_type(type) {

}

GraphBlockStmtImpl::~GraphBlockStmtImpl() {
	// TODO Auto-generated destructor stub
}

const std::vector<IGraphStmt *> &GraphBlockStmtImpl::getStmts() const {
	return m_stmts;
}

void GraphBlockStmtImpl::add(IGraphStmt *stmt) {
	m_stmts.push_back(stmt);
}

} /* namespace psi */
