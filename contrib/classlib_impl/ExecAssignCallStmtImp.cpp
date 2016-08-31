/*
 * ExecAssignCallStmtImp.cpp
 *
 *  Created on: Aug 29, 2016
 *      Author: ballance
 */

#include "ExecAssignCallStmtImp.h"

namespace pss {

ExecAssignCallStmtImp::ExecAssignCallStmtImp(
		const FieldItem				&lhs,
		AssignOp					op,
		const ExecImportCallStmt	&rhs) :
	ExecAssignStmtImp(StmtType_AssignCall, lhs, op), m_rhs(rhs) {

}

ExecAssignCallStmtImp::~ExecAssignCallStmtImp() {
	// TODO Auto-generated destructor stub
}

} /* namespace pss */
