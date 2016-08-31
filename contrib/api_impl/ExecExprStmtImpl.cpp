/*
 * ExecExprStmtImpl.cpp
 *
 *  Created on: Aug 30, 2016
 *      Author: ballance
 */

#include "ExecExprStmtImpl.h"

namespace psi {

ExecExprStmtImpl::ExecExprStmtImpl(
		IFieldRef				*target,
		IExecStmt::AssignOp		op,
		IExpr					*expr) :
				ExecStmtImpl(IExecStmt::StmtType_Expr, target, op), m_expr(expr) {
	// TODO Auto-generated constructor stub

}

ExecExprStmtImpl::~ExecExprStmtImpl() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
