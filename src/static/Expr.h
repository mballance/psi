/*
 * Expr.h
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef EXPR_H_
#define EXPR_H_

#include "Types.h"
#include <memory>

namespace psi {

class Type;

#define DECLARE_OP_FUNCTIONS(_prefix, _op) \
	_prefix Expr operator _op (const Expr &lhs, const Expr &rhs); \
	_prefix Expr operator _op (const Type &lhs, const Expr &rhs); \
	_prefix Expr operator _op (int32_t lhs, const Expr &rhs);     \
	_prefix Expr operator _op (uint32_t lhs, const Expr &rhs);    \


class ExprCore;
class Expr {

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

	private:
		std::shared_ptr<ExprCore>	m_core;


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
