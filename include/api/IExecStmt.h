/*
 * IExecStmt.h
 *
 *  Created on: Aug 12, 2016
 *      Author: ballance
 */

#ifndef INCLUDE_API_IEXECSTMT_H_
#define INCLUDE_API_IEXECSTMT_H_
#include <vector>
#include "api/IExpr.h"
#include "api/IImportFunc.h"
#include "api/IFieldRef.h"

namespace psi_api {

class IExecStmt {
public:

	enum StmtType {
		StmtType_Expr,
		StmtType_Call
	};

	enum AssignOp {
		AssignOp_None, // no assignment
		AssignOp_Eq,
		AssignOp_AndEq,
		AssignOp_OrEq,
		AssignOp_PlusEq,
		AssignOp_MinusEq,
		AssignOp_LShiftEq,
		AssignOp_RShiftEq
	};

	virtual ~IExecStmt() { }

	virtual StmtType getStmtType() = 0;

	virtual IFieldRef *getTarget() = 0;

	virtual AssignOp getAssignOp() = 0;

};

}



#endif /* INCLUDE_API_IEXECSTMT_H_ */
