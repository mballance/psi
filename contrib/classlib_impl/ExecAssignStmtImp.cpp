/*
 * ExecAssignStmtImp.cpp
 *
 *  Created on: Aug 29, 2016
 *      Author: ballance
 */

#include "ExecAssignStmtImp.h"

namespace pss {

ExecAssignStmtImp::ExecAssignStmtImp(
		StmtType			type,
		const FieldItem 	&lhs,
		AssignOp 			op) : ExecStmtImp(type), m_lhs(lhs), m_op(op) {
}

ExecAssignStmtImp::~ExecAssignStmtImp() {
	// TODO Auto-generated destructor stub
}

} /* namespace pss */

