/*
 * ExecAssignStmtImp.h
 *
 *  Created on: Aug 29, 2016
 *      Author: ballance
 */

#ifndef CONTRIB_CLASSLIB_IMPL_EXECASSIGNSTMTIMP_H_
#define CONTRIB_CLASSLIB_IMPL_EXECASSIGNSTMTIMP_H_

#include "ExecStmtImp.h"
#include "classlib/Expr.h"

namespace pss {

class ExecAssignStmtImp: public ExecStmtImp {
public:

	enum AssignOp {
		AssignOp_Nop,
		AssignOp_Eq,
		AssignOp_AndEq,
		AssignOp_OrEq
	};

public:
	ExecAssignStmtImp(
			StmtType			type,
			const FieldItem 	&lhs,
			AssignOp 			op);

	virtual ~ExecAssignStmtImp();

	const FieldItem &lhs() const {
		return m_lhs;
	}

	AssignOp getOp() const {
		return m_op;
	}

private:
	FieldItem			m_lhs;
	AssignOp			m_op;
};

} /* namespace pss */

#endif /* CONTRIB_CLASSLIB_IMPL_EXECASSIGNSTMTIMP_H_ */

