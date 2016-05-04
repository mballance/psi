/*
 * Expr.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "classlib/Expr.h"

#include <stdio.h>
#include "classlib/ExprCore.h"
#include "classlib/Type.h"

namespace psi {

Expr::Expr() : m_core(nullptr) {

}

Expr::Expr(uint32_t v) : m_core(new ExprCore(v)) {

}

Expr::Expr(int32_t v) : m_core(new ExprCore(v)) {

}

Expr::Expr(const Type &t) : m_core(new ExprCore(t)) {

}

Expr::Expr(const Expr &rhs) : m_core(rhs.m_core) {

}

Expr::Expr(ExprCore *rhs) : m_core(rhs) {

}

Expr::~Expr() {
	// TODO Auto-generated destructor stub
}

Expr Expr::operator [] (const Expr &rhs) {
	return Expr(new ExprCore(BinOp_ArrayRef, *this, rhs));
}

Expr Expr::operator [] (int32_t rhs) {
	return Expr(new ExprCore(BinOp_ArrayRef, *this, rhs));
}

Expr Expr::operator [] (uint32_t rhs) {
	return Expr(new ExprCore(BinOp_ArrayRef, *this, rhs));
}

void Expr::build() {
	if (m_core.ptr() != nullptr) {
		m_core->m_lhs.build();
		m_core->m_rhs.build();
	}
}

const char *Expr::toString(Operator op) {
	switch (op) {
		case LiteralUint: return "uint32_t";
		case LiteralInt: return "int32_t";
		case LiteralBit: return "bit";
		case LiteralBool: return "bool";
		case LiteralString: return "string";
		case BinOp_EqEq: return "==";
		case BinOp_NotEq: return "!=";
		case BinOp_GE: return ">=";
		case BinOp_GT: return ">";
		case BinOp_LE: return "<=";
		case BinOp_LT: return "<";
		case BinOp_And: return "&";
		case BinOp_AndAnd: return "&&";
		case BinOp_Or: return "|";
		case BinOp_OrOr: return "||";
		case BinOp_Minus: return "-";
		case BinOp_Plus: return "+";
		case BinOp_Multiply: return "*";
		case BinOp_Divide: return "/";
		case BinOp_Mod: return "%";
		case BinOp_ArrayRef: return "arrayref";
		case TypeRef: return "typeref";
	}

	return "UNKNOWN";
}

#define DEFINE_OP_FUNCTIONS(_op, _code) \
	Expr operator _op (const Expr &lhs, const Expr &rhs) { \
		return Expr(new ExprCore(_code, lhs, rhs)); \
	} \
	Expr operator _op (const Type &lhs, const Expr &rhs) { \
		return Expr(new ExprCore(_code, lhs, rhs)); \
	} \
	Expr operator _op (int32_t lhs, const Expr &rhs) { \
		return Expr(new ExprCore(_code, lhs, rhs)); \
	} \
	Expr operator _op (uint32_t lhs, const Expr &rhs) { \
		return Expr(new ExprCore(_code, lhs, rhs)); \
	}


DEFINE_OP_FUNCTIONS(==, Expr::BinOp_EqEq)
DEFINE_OP_FUNCTIONS(!=, Expr::BinOp_NotEq)
DEFINE_OP_FUNCTIONS(>=, Expr::BinOp_GE)
DEFINE_OP_FUNCTIONS(>, Expr::BinOp_GT)
DEFINE_OP_FUNCTIONS(<=, Expr::BinOp_LE)
DEFINE_OP_FUNCTIONS(<, Expr::BinOp_LT)
DEFINE_OP_FUNCTIONS(&, Expr::BinOp_And)
DEFINE_OP_FUNCTIONS(&&, Expr::BinOp_AndAnd)
DEFINE_OP_FUNCTIONS(|, Expr::BinOp_Or)
DEFINE_OP_FUNCTIONS(||, Expr::BinOp_OrOr)
DEFINE_OP_FUNCTIONS(-, Expr::BinOp_Minus)
DEFINE_OP_FUNCTIONS(+, Expr::BinOp_Plus)
DEFINE_OP_FUNCTIONS(*, Expr::BinOp_Multiply)
DEFINE_OP_FUNCTIONS(/, Expr::BinOp_Divide)
DEFINE_OP_FUNCTIONS(%, Expr::BinOp_Mod)

} /* namespace psi */
