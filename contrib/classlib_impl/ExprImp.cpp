/*
 * ExprImp.cpp
 *
 * Copyright 2016 Mentor Graphics Corporation
 * All Rights Reserved Worldwide
 *
 * Licensed under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in
 *  compliance with the License.  You may obtain a copy of
 *  the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in
 * writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.  See
 * the License for the specific language governing
 * permissions and limitations under the License.
 * 
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "ExprImp.h"
#include "ExprCore.h"

#include <stdio.h>

namespace pss {

ExprImp::ExprImp() : SharedPtr<ExprCore>(0) {

}

ExprImp::ExprImp(ExprCore *p) : SharedPtr<ExprCore>(p)  {

}

ExprImp::ExprImp(const ExprImp &p) : SharedPtr<ExprCore>(p)  {

}

ExprImp::ExprImp(const expr &p) : SharedPtr<ExprCore>(p.imp())  {

}

ExprImp::~ExprImp() {

}

expr::expr() : m_core(new ExprImp(0)) {

}

expr::expr(uint32_t v) : m_core(new ExprImp(new ExprCore(v))) { }

expr::expr(int32_t v) : m_core(new ExprImp(new ExprCore(v))) { }

expr::expr(const base_item &t) : m_core(new ExprImp(new ExprCore(t))) { }

expr::expr(const ExprImp &ptr) : m_core(new ExprImp(ptr)) { }

expr::expr(const expr &rhs) : m_core(new ExprImp(rhs.imp())) { }

// expr::expr(ExprCore *rhs) : m_core(rhs) { }

expr::~expr() {
	if (m_core) {
		delete m_core;
	}
}

//bool ExprImp::isBinOp() const {
//	if (m_core.ptr()) {
//		return isBinOp(m_core->m_op);
//	}
//	return false;
//}

expr_list_builder expr::operator,(const expr &rhs) {
	return expr_list_builder(*this, rhs);
}

bool ExprImp::isBinOp(Operator op) {
	return (op >= BinOp_EqEq && op <= BinOp_ArrayRef);
}

ExprImp::Operator ExprImp::getOp() const {
	return ptr()->getOp();
}

expr expr::operator [] (const expr &rhs) {
	return expr(new ExprCore(ExprImp::BinOp_ArrayRef, *this, rhs));
}

expr expr::operator [] (int32_t rhs) {
	return expr(new ExprCore(ExprImp::BinOp_ArrayRef, *this, rhs));
}

expr expr::operator [] (uint32_t rhs) {
	return expr(new ExprCore(ExprImp::BinOp_ArrayRef, *this, rhs));
}

expr expr::inside(const expr_list &rhs) {
	return expr(new ExprCore(ExprImp::BinOp_Inside, *this, rhs));
}

expr expr::implies(const expr_list &rhs) {
	return expr(new ExprCore(ExprImp::Stmt_Implies, *this, rhs));
}

const char *ExprImp::toString(Operator op) {
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
		case Stmt_If: return "if";
		case Stmt_IfElse: return "if/else";
		case List: return "list";
		case TypeRef: return "typeref";
	}

	return "UNKNOWN";
}

//expr operator _op (const base_item &lhs, const expr &rhs) { \
//	return expr(new ExprCore(_code, lhs, rhs)); \
//} \

#define DEFINE_OP_FUNCTIONS(_op, _code) \
expr expr::operator _op (const expr &rhs) { \
  return expr(new ExprCore(_code, *this, rhs)); \
}

//DEFINE_OP_FUNCTIONS(=, ExprImp::BinOp_Eq)
DEFINE_OP_FUNCTIONS(==, ExprImp::BinOp_EqEq)
DEFINE_OP_FUNCTIONS(!=, ExprImp::BinOp_NotEq)
DEFINE_OP_FUNCTIONS(>=, ExprImp::BinOp_GE)
DEFINE_OP_FUNCTIONS(>, ExprImp::BinOp_GT)
DEFINE_OP_FUNCTIONS(<=, ExprImp::BinOp_LE)
DEFINE_OP_FUNCTIONS(<, ExprImp::BinOp_LT)
DEFINE_OP_FUNCTIONS(&, ExprImp::BinOp_And)
DEFINE_OP_FUNCTIONS(&&, ExprImp::BinOp_AndAnd)
DEFINE_OP_FUNCTIONS(|, ExprImp::BinOp_Or)
DEFINE_OP_FUNCTIONS(||, ExprImp::BinOp_OrOr)
DEFINE_OP_FUNCTIONS(-, ExprImp::BinOp_Minus)
DEFINE_OP_FUNCTIONS(+, ExprImp::BinOp_Plus)
DEFINE_OP_FUNCTIONS(*, ExprImp::BinOp_Multiply)
DEFINE_OP_FUNCTIONS(/, ExprImp::BinOp_Divide)
DEFINE_OP_FUNCTIONS(%, ExprImp::BinOp_Mod)

const ExprImp &expr::imp() const {
	return *m_core;
}

} /* namespace pss */
