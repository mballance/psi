/*
 * ExecStmtImpl.h
 *
 *  Created on: Aug 30, 2016
 *      Author: ballance
 */

#ifndef CONTRIB_API_IMPL_EXECSTMTIMPL_H_
#define CONTRIB_API_IMPL_EXECSTMTIMPL_H_
#include "api/IExecStmt.h"

using namespace psi_api;

namespace psi {

class ExecStmtImpl : public virtual IExecStmt {
public:

	ExecStmtImpl(
			IExecStmt::StmtType type,
			IField				*target,
			IExecStmt::AssignOp	op);

	virtual ~ExecStmtImpl();


	virtual StmtType getStmtType() { return m_type; }

	virtual IField *getTarget()  { return m_target; }

	virtual AssignOp getAssignOp() { return m_op; }

private:
	IExecStmt::StmtType				m_type;
	IField							*m_target;
	IExecStmt::AssignOp				m_op;
};

} /* namespace psi */

#endif /* CONTRIB_API_IMPL_EXECSTMTIMPL_H_ */
