/*
 * ExprCore.cpp
 *
 *  Created on: Apr 27, 2016
 *      Author: ballance
 */

#include "classlib/ExprCore.h"

#include "classlib/Expr.h"

namespace psi {

ExprCore::ExprCore(uint32_t v) : m_op(Expr::LiteralUint) {
	m_val.ui = v;
}

ExprCore::ExprCore(int32_t v) : m_op(Expr::LiteralInt) {
	m_val.i = v;
}

ExprCore::ExprCore(const Type &t) : m_op(Expr::TypeRef) {
	m_val.ref = &t;
}

ExprCore::ExprCore(Expr::Operator op, const Expr &lhs, const Expr &rhs) :
	m_op(op), m_lhs(lhs), m_rhs(rhs) {
}

ExprCore::~ExprCore() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
