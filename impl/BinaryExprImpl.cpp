/*
 * BinaryExprImpl.cpp
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#include "BinaryExprImpl.h"

namespace psi {

BinaryExprImpl::BinaryExprImpl(
		IExpr					*lhs,
		IBinaryExpr::BinOpType	op,
		IExpr					*rhs) : m_lhs(lhs), m_rhs(rhs), m_op(op) { }

BinaryExprImpl::~BinaryExprImpl() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
