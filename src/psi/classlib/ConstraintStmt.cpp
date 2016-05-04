/*
 * ConstraintStmt.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "classlib/ConstraintStmt.h"

namespace psi {

ConstraintStmt::ConstraintStmt(const Expr &expr) {
	Expr e = expr;
	e.build();

}

ConstraintStmt::~ConstraintStmt() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
