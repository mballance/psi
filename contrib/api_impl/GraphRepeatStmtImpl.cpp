/*
 * GraphRepeatStmtImpl.cpp
 *
 *  Created on: Jun 10, 2016
 *      Author: ballance
 */

#include "../api_impl/GraphRepeatStmtImpl.h"

namespace psi {

GraphRepeatStmtImpl::GraphRepeatStmtImpl(RepeatType type, IExpr *cond, IGraphStmt *stmt) :
	m_type(type), m_cond(cond), m_body(stmt) {
}

GraphRepeatStmtImpl::~GraphRepeatStmtImpl() {
	// TODO Auto-generated destructor stub
}

void GraphRepeatStmtImpl::setBody(IGraphStmt *s) {
	m_body = s;
}

} /* namespace psi */
