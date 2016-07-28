/*
 * ExprCore.cpp
 *
 *  Created on: Jul 28, 2016
 *      Author: ballance
 */
#include "ExprCore.h"
#include "classlib/Import.h"

namespace psi {

ExprCore::ExprCore(uint32_t v) {
	m_val.ui = v;
	m_op = ExprImp::LiteralBit;
}

ExprCore::ExprCore(int32_t v) {
	m_val.i = v;
	m_op = ExprImp::LiteralInt;
}

ExprCore::ExprCore(const BaseItem &t) {
	m_val.ref = t.impl();
	m_op = ExprImp::TypeRef;
}

ExprCore::ExprCore(
		ExprImp::Operator 	op,
		const Expr 			&lhs,
		const Expr 			&rhs) : m_op(op), m_lhs(lhs.imp()), m_rhs(rhs.imp()) {

}

ExprCore::ExprCore(Import &import, const Expr &params) :
		m_op(ExprImp::ImportCall), m_lhs(params) {
	m_val.ref = import.impl();
}

ExprCore::ExprCore(ExprImp::Operator op) : m_op(op) { }

ExprCore::~ExprCore() {

}

}


