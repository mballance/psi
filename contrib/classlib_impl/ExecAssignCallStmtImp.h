/*
 * ExecAssignCallStmtImp.h
 *
 *  Created on: Aug 29, 2016
 *      Author: ballance
 */

#ifndef CONTRIB_CLASSLIB_IMPL_EXECASSIGNCALLSTMTIMP_H_
#define CONTRIB_CLASSLIB_IMPL_EXECASSIGNCALLSTMTIMP_H_

#include "ExecAssignStmtImp.h"
#include "classlib/ExecImportCallStmt.h"
#include "classlib/FieldItem.h"

namespace pss {

class ExecAssignCallStmtImp: public ExecAssignStmtImp {
public:
	ExecAssignCallStmtImp(
			const FieldItem				&lhs,
			AssignOp					op,
			const ExecImportCallStmt	&rhs);

	virtual ~ExecAssignCallStmtImp();

	const ExecImportCallStmt &rhs() const { return m_rhs; }

private:
	ExecImportCallStmt				m_rhs;

};

} /* namespace pss */

#endif /* CONTRIB_CLASSLIB_IMPL_EXECASSIGNCALLSTMTIMP_H_ */
