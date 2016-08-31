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
		StmtType_AssignExpr,
		StmtType_AssignCall,
		StmtType_Call
	};

public:
	ExecStmtImp(StmtType type);

	virtual ~ExecStmtImp();

	void inc_refcnt();

	void dec_refcnt();

	StmtType getStmtType() const { return m_type; }

private:
	uint32_t				m_refcnt;
	StmtType				m_type;
};

} /* namespace pss */

#endif /* CONTRIB_CLASSLIB_IMPL_EXECSTMTIMP_H_ */
