/*
 * ExecExprStmtImpl.h
 *
 *  Created on: Aug 30, 2016
 *      Author: ballance
 */

#ifndef CONTRIB_API_IMPL_EXECEXPRSTMTIMPL_H_
#define CONTRIB_API_IMPL_EXECEXPRSTMTIMPL_H_

#include "ExecStmtImpl.h"
#include "api/IExecExprStmt.h"

namespace psi {

class ExecExprStmtImpl:
		public virtual ExecStmtImpl,
		public virtual IExecExprStmt {
public:

	ExecExprStmtImpl(
			IFieldRef			*target,
			IExecStmt::AssignOp	op,
			IExpr				*expr
			);

	virtual ~ExecExprStmtImpl();

	virtual IExpr *getExpr() { return m_expr; }

private:
	IExpr						*m_expr;
};

} /* namespace psi */

#endif /* CONTRIB_API_IMPL_EXECEXPRSTMTIMPL_H_ */
