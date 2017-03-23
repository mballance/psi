/*
 * ExecStmtImp.h
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

#ifndef CONTRIB_CLASSLIB_IMPL_EXECSTMTIMP_H_
#define CONTRIB_CLASSLIB_IMPL_EXECSTMTIMP_H_
#include "../../include/prv/expr.h"
#include "../vendor/attr_item_impl.h"
#include "classlib/exec_stmt.h"

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
