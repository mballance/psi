/*
 * ExecCallStmtImpl.h
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
 *
 *  Created on: Aug 30, 2016
 *      Author: ballance
 */

#ifndef CONTRIB_API_IMPL_EXECCALLSTMTIMPL_H_
#define CONTRIB_API_IMPL_EXECCALLSTMTIMPL_H_

#include "ExecStmtImpl.h"
#include "api/IExecCallStmt.h"
#include "BaseItemImpl.h"

namespace psi {

class ExecCallStmtImpl:
		public virtual ExecStmtImpl,
		public virtual IExecCallStmt {
public:

	ExecCallStmtImpl(
			IFieldRef					*target,
			IExecStmt::AssignOp			op,
			IImportFunc					*func,
			const std::vector<IExpr *>	&parameters);
#ifdef PSS_HAVE_CXX_11
	ExecCallStmtImpl(
			IFieldRef						*target,
			IExecStmt::AssignOp				op,
			IImportFunc						*func,
			std::initializer_list<IExpr *>	parameters) :
				ExecCallStmtImpl(target, op, func, std::vector<IExpr *>(parameters)) { }
#endif

	virtual ~ExecCallStmtImpl();

	virtual IImportFunc *getFunc() { return m_func; }

	virtual std::vector<IExpr *> &getParameters() { return m_parameters; }

private:
	IImportFunc						*m_func;
	std::vector<IExpr *>			m_parameters;
};

} /* namespace psi */

#endif /* CONTRIB_API_IMPL_EXECCALLSTMTIMPL_H_ */
