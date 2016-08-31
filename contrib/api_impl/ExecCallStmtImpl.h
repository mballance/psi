/*
 * ExecCallStmtImpl.h
 *
 *  Created on: Aug 30, 2016
 *      Author: ballance
 */

#ifndef CONTRIB_API_IMPL_EXECCALLSTMTIMPL_H_
#define CONTRIB_API_IMPL_EXECCALLSTMTIMPL_H_

#include "ExecStmtImpl.h"
#include "api/IExecCallStmt.h"

namespace psi {

class ExecCallStmtImpl:
		public virtual ExecStmtImpl,
		public virtual IExecCallStmt {
public:

	ExecCallStmtImpl(
			IField						*target,
			IExecStmt::AssignOp			op,
			IImportFunc					*func,
			const std::vector<IExpr *>	&parameters);

	virtual ~ExecCallStmtImpl();

	virtual IImportFunc *getFunc() { return m_func; }

	virtual std::vector<IExpr *> &getParameters() { return m_parameters; }

private:
	IImportFunc						*m_func;
	std::vector<IExpr *>			m_parameters;
};

} /* namespace psi */

#endif /* CONTRIB_API_IMPL_EXECCALLSTMTIMPL_H_ */
