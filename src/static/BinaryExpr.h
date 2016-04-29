/*
 * BinaryExpr.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_BINARYEXPR_H_
#define SRC_STATIC_BINARYEXPR_H_

#include "Expr.h"
#include "Type.h"

namespace psi {

class BinaryExpr: public Expr {

	public:
		enum BinOp {
			BinOp_Plus,
			BinOp_Minus,
			BinOp_And,
			BinOp_Or,
			BinOp_AndAnd,
			BinOp_OrOr,
			BinOp_EqEq,
			BinOp_NotEq,
			BinOp_GE,
			BinOp_LE,
			BinOp_GT,
			BinOp_LT,
			BinOp_LShift,
			BinOp_RShift
		};

	public:

		BinaryExpr(const Expr &lhs, BinOp op, const Expr &rhs);

		BinaryExpr(const Type &lhs, BinOp op, const Expr &rhs);

		BinaryExpr(const Expr &lhs, BinOp op, const Type &rhs);

		BinaryExpr(const Type &lhs, BinOp op, const Type &rhs);

		virtual ~BinaryExpr();

	private:
		Expr					m_lhs;
		BinOp					m_binop;
		Expr					m_rhs;
};

} /* namespace psi */

#endif /* SRC_STATIC_BINARYEXPR_H_ */
