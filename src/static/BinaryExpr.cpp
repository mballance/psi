/*
 * BinaryExpr.cpp
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#include "BinaryExpr.h"
#include "TypeExpr.h"

namespace psi {

BinaryExpr::BinaryExpr(const Expr &lhs, BinOp op, const Expr &rhs) :
	Expr(Expr::BinaryExpr), m_lhs(lhs), m_binop(op), m_rhs(rhs) { }

BinaryExpr::BinaryExpr(const Expr &lhs, BinOp op, const Type &rhs) :
	Expr(Expr::BinaryExpr), m_lhs(lhs), m_binop(op), m_rhs(TypeExpr(rhs)) { }

BinaryExpr::BinaryExpr(const Type &lhs, BinOp op, const Expr &rhs) :
	Expr(Expr::BinaryExpr), m_lhs(TypeExpr(lhs)), m_binop(op), m_rhs(rhs) { }

BinaryExpr::BinaryExpr(const Type &lhs, BinOp op, const Type &rhs) :
	Expr(Expr::BinaryExpr), m_lhs(TypeExpr(lhs)), m_binop(op), m_rhs(TypeExpr(rhs)) { }

BinaryExpr::~BinaryExpr() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
