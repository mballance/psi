/*
 * ExecAssignExprStmtImp.cpp
 *
 *  Created on: Aug 29, 2016
 *      Author: ballance
 */

#include "ExecAssignExprStmtImp.h"

namespace pss {

ExecAssignExprStmtImp::ExecAssignExprStmtImp(
		const FieldItem			&lhs,
		AssignOp				op,
		const Expr				&rhs) :
	ExecAssignStmtImp(StmtType_AssignExpr, lhs, op), m_rhs(rhs) {

}

ExecAssignExprStmtImp::~ExecAssignExprStmtImp() {
	// TODO Auto-generated destructor stub
}

} /* namespace pss */
