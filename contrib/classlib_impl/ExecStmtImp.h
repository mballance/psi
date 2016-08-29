/*
 * ExecStmtImp.h
 *
 *  Created on: Aug 29, 2016
 *      Author: ballance
 */

#ifndef CONTRIB_CLASSLIB_IMPL_EXECSTMTIMP_H_
#define CONTRIB_CLASSLIB_IMPL_EXECSTMTIMP_H_
#include "classlib/ExecStmt.h"
#include "classlib/FieldItem.h"
#include "classlib/Expr.h"

namespace pss {

class ExecStmtImp {
public:
	enum StmtType {
		StmtType_Call,
		StmtType_EqCall,
		StmtType_EqExpr
	};

public:
	ExecStmtImp(StmtType op);

	ExecStmtImp(
			const FieldItem				&lhs,
			StmtType					op,
			const ExecImportCallStmt	&rhs
			);

	ExecStmtImp(
			const FieldItem				&lhs,
			StmtType					op,
			const Expr					&rhs
			);

	virtual ~ExecStmtImp();

	void inc_refcnt();

	void dec_refcnt();

private:
	uint32_t				m_refcnt;
};

} /* namespace pss */

#endif /* CONTRIB_CLASSLIB_IMPL_EXECSTMTIMP_H_ */
