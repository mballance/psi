/*
 * ConstraintStmt.h
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef CONSTRAINTSTMT_H_
#define CONSTRAINTSTMT_H_
#include "classlib/Expr.h"
#include "classlib/ExprList.h"

namespace psi {

class ConstraintStmt {

	public:
		ConstraintStmt(const ExprList &expr);
//		ConstraintStmt(const Expr &expr);

		virtual ~ConstraintStmt();

		Expr &getExpr() { return m_expr; }

	private:

		Expr				m_expr;
};

} /* namespace psi */

#endif /* CONSTRAINTSTMT_H_ */
