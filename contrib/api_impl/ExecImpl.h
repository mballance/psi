/*
 * ExecImpl.h
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
 *  Created on: Jun 1, 2016
 *      Author: ballance
 */

#ifndef IMPL_EXECIMPL_H_
#define IMPL_EXECIMPL_H_
#include "api/IExec.h"
#include "BaseItemImpl.h"

using namespace psi_api;

namespace psi {

class ExecImpl :
		public virtual IExec,
		public virtual BaseItemImpl {
public:
	ExecImpl(
			ExecKind			kind,
			const std::string	&language,
			const std::string	&text);

	ExecImpl(
			ExecKind			kind,
			IExecCallback		*exec);

	ExecImpl(
			ExecKind						kind,
			const std::vector<IExecStmt *>	&stmts);

#ifdef PSS_HAVE_CXX_11
	ExecImpl(
			ExecKind							kind,
			std::initializer_list<IExecStmt *>	stmts) :
				ExecImpl(kind, std::vector<IExecStmt *>(stmts)) { }
#endif

	ExecImpl();

	virtual ~ExecImpl();

	virtual ExecKind getExecKind() { return m_execKind; }

	virtual ExecType getExecType() { return m_execType; }

	virtual const std::string &getLanguage() const { return m_language; }

	/**
	 * Returns the target-template string for
	 * exec type TargetTemplate
	 */
	virtual const std::string &getTargetTemplate() {
		return m_targetTemplate;
	}

	/**
	 * Returns the inline-exec closure for exec type Inline
	 */
	virtual IExecCallback *getInlineExec() { return m_inlineExec; }

	/**
	 * Returns the native-exec statement list
	 */
	virtual const std::vector<IExecStmt *> &getStmts() { return m_stmts; }

	std::vector<IExecStmt *> &getStmtsM();

	void addStmt(IExecStmt *s);

private:
	ExecKind					m_execKind;
	ExecType					m_execType;
	std::string					m_language;
	std::string					m_targetTemplate;
	IExecCallback				*m_inlineExec;
	std::vector<IExecStmt *>	m_stmts;

};

} /* namespace psi */

#endif /* IMPL_EXECIMPL_H_ */
