/*
 * ConstraintStmt.h
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef CONSTRAINTSTMT_H_
#define CONSTRAINTSTMT_H_
#include "Expr.h"

namespace psi {

class ConstraintStmt {

	public:
		ConstraintStmt(const Expr &expr);

		virtual ~ConstraintStmt();
};

} /* namespace psi */

#endif /* CONSTRAINTSTMT_H_ */
