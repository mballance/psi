/*
 * ExecStmtImpl.cpp
 *
 *  Created on: Aug 30, 2016
 *      Author: ballance
 */

#include "ExecStmtImpl.h"

namespace psi {

ExecStmtImpl::ExecStmtImpl(
		IExecStmt::StmtType		type,
		IField					*target,
		IExecStmt::AssignOp		op) : m_type(type), m_target(target), m_op(op) {

}

ExecStmtImpl::~ExecStmtImpl() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
