/*
 * Expr.h
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef EXPR_H_
#define EXPR_H_

#include "classlib/SharedPtr.h"
#include "classlib/Types.h"

namespace psi {

class Type;

#define DECLARE_OP_FUNCTIONS(_prefix, _op) \
	_prefix Expr operator _op (const Expr &lhs, const Expr &rhs); \
	_prefix Expr operator _op (const Type &lhs, const Expr &rhs); \
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

			BinOp_EqEq,
			BinOp_NotEq,
			BinOp_GE,
			BinOp_GT,
			BinOp_LE,
			BinOp_LT,
			BinOp_And,
			BinOp_AndAnd,
			BinOp_Or,
			BinOp_OrOr,
			BinOp_Minus,
			BinOp_Plus,
			BinOp_Multiply,
			BinOp_Divide,
			BinOp_Mod,
			BinOp_ArrayRef,

			Stmt_If,
			Stmt_IfElse,

			List,
			TypeRef
		};

	public:
		Expr();

		Expr(uint32_t v);

		Expr(int v);

		Expr(const Type &t);

		Expr(const Expr &rhs);

		Expr(ExprCore *rhs);

		virtual ~Expr();

		void build();

		const SharedPtr<ExprCore> &getCore() const { return m_core; }

		SharedPtr<ExprCore> &getCore() { return m_core; }

		ExprCore *getCorePtr() const { return m_core.ptr(); }

		Operator getOp() const;

		bool isBinOp() const;

		static bool isBinOp(Operator op);

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

#endif /* EXPR_H_ */
