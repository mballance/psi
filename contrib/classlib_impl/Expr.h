/*
 * Expr.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_EXPR_H
#define INCLUDED_EXPR_H

#include "classlib/Types.h"
#include "SharedPtr.h"

namespace psi {

class ExprListBuilder;
class BaseItem;

#define DECLARE_OP_FUNCTIONS(_prefix, _op) \
	_prefix Expr operator _op (const Expr &lhs, const Expr &rhs); \
	_prefix Expr operator _op (int32_t lhs, const Expr &rhs);     \
	_prefix Expr operator _op (uint32_t lhs, const Expr &rhs);    \


class ExprCore;
class ExprCoreList;
class Expr {

	friend class ExprCoreList;

	public:
		enum Operator {
			LiteralUint,
			LiteralInt,
			LiteralBit,
			LiteralBool,
			LiteralString,

			BinOp_Eq,
			BinOp_EqEq,
			BinOp_NotEq,
			BinOp_GE,
			BinOp_GT,
			BinOp_LE, // 10
			BinOp_LT,
			BinOp_And,
			BinOp_AndAnd,
			BinOp_Or,
			BinOp_OrOr,
			BinOp_Minus,
			BinOp_Plus,
			BinOp_Multiply,
			BinOp_Divide,
			BinOp_Mod, // 20
			BinOp_ArrayRef,

			Stmt_If,
			Stmt_IfElse,

			GraphParallel,
			GraphRepeat, // 25
			GraphSchedule,
			GraphSelect,
			GraphWith,

			ImportCall,

			List, // 30
			TypeRef
		};

	public:
		Expr();

		Expr(uint32_t v);

		Expr(int32_t v);

		Expr(const BaseItem &t);

		Expr(const Expr &rhs);

		Expr(ExprCore *rhs);

		Expr(const SharedPtr<ExprCore> &ptr);

		virtual ~Expr();

		void build();

		const SharedPtr<ExprCore> &getCore() const { return m_core; }

		SharedPtr<ExprCore> &getCore() { return m_core; }

		// ExprCore *getCorePtr() const { return m_core.ptr(); }

		Operator getOp() const;

		void setOp(Operator op);

		bool isBinOp() const;

		static bool isBinOp(Operator op);

		ExprListBuilder operator,(const Expr &rhs);

		Expr operator [] (const Expr &rhs);

		Expr operator [] (int32_t rhs);

		Expr operator [] (uint32_t rhs);

		DECLARE_OP_FUNCTIONS(friend, ==)
		DECLARE_OP_FUNCTIONS(friend, !=)
		DECLARE_OP_FUNCTIONS(friend, <=)
		DECLARE_OP_FUNCTIONS(friend, <)
		DECLARE_OP_FUNCTIONS(friend, >=)
		DECLARE_OP_FUNCTIONS(friend, >)
		DECLARE_OP_FUNCTIONS(friend, &)
		DECLARE_OP_FUNCTIONS(friend, &&)
		DECLARE_OP_FUNCTIONS(friend, |)
		DECLARE_OP_FUNCTIONS(friend, ||)
		DECLARE_OP_FUNCTIONS(friend, -)
		DECLARE_OP_FUNCTIONS(friend, +)
		DECLARE_OP_FUNCTIONS(friend, *)
		DECLARE_OP_FUNCTIONS(friend, /)
		DECLARE_OP_FUNCTIONS(friend, %)

		static const char *toString(Operator op);

	protected:
		SharedPtr<ExprCore>		m_core;

};

DECLARE_OP_FUNCTIONS( , ==)
DECLARE_OP_FUNCTIONS( , !=)
DECLARE_OP_FUNCTIONS( , <=)
DECLARE_OP_FUNCTIONS( , <)
DECLARE_OP_FUNCTIONS( , >=)
DECLARE_OP_FUNCTIONS( , >)
DECLARE_OP_FUNCTIONS( , &)
DECLARE_OP_FUNCTIONS( , &&)
DECLARE_OP_FUNCTIONS( , |)
DECLARE_OP_FUNCTIONS( , ||)
DECLARE_OP_FUNCTIONS( , -)
DECLARE_OP_FUNCTIONS( , +)
DECLARE_OP_FUNCTIONS( , *)
DECLARE_OP_FUNCTIONS( , /)
DECLARE_OP_FUNCTIONS( , %)

#undef DECLARE_OP_FUNCTIONS


} /* namespace psi */

#endif /* INCLUDED_EXPR_H */
