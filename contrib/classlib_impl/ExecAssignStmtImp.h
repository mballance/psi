/*
 * ExecAssignStmtImp.h
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
 *  Created on: Aug 29, 2016
 *      Author: ballance
 */

#ifndef CONTRIB_CLASSLIB_IMPL_EXECASSIGNSTMTIMP_H_
#define CONTRIB_CLASSLIB_IMPL_EXECASSIGNSTMTIMP_H_

#include "ExecStmtImp.h"
#include "classlib/expr.h"

namespace pss {

class ExecAssignStmtImp: public ExecStmtImp {
public:

	enum AssignOp {
		AssignOp_Nop,
		AssignOp_Eq,
		AssignOp_PlusEq,
		AssignOp_MinusEq,
		AssignOp_LShiftEq,
		AssignOp_RShiftEq,
		AssignOp_AndEq,
		AssignOp_OrEq
	};

public:
	ExecAssignStmtImp(
			StmtType			type,
			const attr_item 	&lhs,
			AssignOp 			op);

	virtual ~ExecAssignStmtImp();

	const attr_item &lhs() const {
		return m_lhs;
	}

	AssignOp getOp() const {
		return m_op;
	}

private:
	attr_item			m_lhs;
	AssignOp			m_op;
};

} /* namespace pss */

#endif /* CONTRIB_CLASSLIB_IMPL_EXECASSIGNSTMTIMP_H_ */

