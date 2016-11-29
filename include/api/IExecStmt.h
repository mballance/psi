/*
 * IExecStmt.h
 *
 * Copyright 2016 Mentor Graphics Corporation
 * All Rights Reserved Worldwide
 *
 * Licensed under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in
 *  compliance with the License.  You may obtain a copy of
 *  the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in
 * writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.  See
 * the License for the specific language governing
 * permissions and limitations under the License.
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
		StmtType_Call,
		StmtType_Vendor
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
