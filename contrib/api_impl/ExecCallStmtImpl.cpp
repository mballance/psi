/*
 * ExecCallStmtImpl.cpp
 *
 *  Created on: Aug 30, 2016
 *      Author: ballance
 */

#include "ExecCallStmtImpl.h"

namespace psi {

ExecCallStmtImpl::ExecCallStmtImpl(
		IField						*target,
		IExecStmt::AssignOp			op,
		IImportFunc					*func,
		const std::vector<IExpr *>	&parameters) :
				ExecStmtImpl(IExecStmt::StmtType_Call, target, op),
				m_func(func), m_parameters(parameters) {

}

ExecCallStmtImpl::~ExecCallStmtImpl() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
