/*
 * ExecAssignExprStmtImp.h
 *
 *  Created on: Aug 29, 2016
 *      Author: ballance
 */

#ifndef CONTRIB_CLASSLIB_IMPL_EXECASSIGNEXPRSTMTIMP_H_
#define CONTRIB_CLASSLIB_IMPL_EXECASSIGNEXPRSTMTIMP_H_

#include "ExecAssignStmtImp.h"

namespace pss {

class ExecAssignExprStmtImp: public ExecAssignStmtImp {
public:
	ExecAssignExprStmtImp(
			const FieldItem		&lhs,
			AssignOp			op,
			const Expr			&rhs
			);

	virtual ~ExecAssignExprStmtImp();

	const Expr &rhs() const { return m_rhs; }

private:
	Expr						m_rhs;
};

} /* namespace pss */

#endif /* CONTRIB_CLASSLIB_IMPL_EXECASSIGNEXPRSTMTIMP_H_ */
