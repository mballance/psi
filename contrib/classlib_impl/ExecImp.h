/*
 * ExecImp.h
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
 *  Created on: Apr 29, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_EXEC_IMP_H
#define INCLUDED_EXEC_IMP_H

#include <string>

#include "classlib/exec.h"
#include "BaseItemImp.h"
#include "classlib/ExecStmtList.h"

namespace pss {

class ExecImp : public BaseItemImp {

	public:
		enum ExecType {
			Null,
			TargetTemplate,
			Native,
			Inline
		};

	public:

		ExecImp(
			exec						*master,
			BaseItem					*p,
			exec::ExecKind 				kind,
			const std::string 			&language,
			const std::string 			&content);

		ExecImp(
			exec						*master,
			ExtendItem					*p,
			exec::ExecKind 				kind,
			const std::string 			&language,
			const std::string 			&content);

		ExecImp(
			exec						*master,
			BaseItem					*p,
			exec::ExecKind 				kind,
			const ExecStmtList			&stmts);

		ExecImp(
			exec						*master,
			ExtendItem					*p,
			exec::ExecKind				kind,
			const ExecStmtList			&stmts);

		/**
		 * Inline exec block that activates the appropriate
		 * hook method in the containing declaration
		 */
		ExecImp(
			exec							*master,
			BaseItem						*p,
			exec::ExecKind					kind);

		virtual ~ExecImp();

		inline exec::ExecKind getExecKind() const {
			return m_execKind;
		}

		inline ExecType getExecType() const {
			return m_execType;
		}

		const std::string &getLanguage() const { return m_language; }

		const std::string &getTargetTemplate() const { return m_content; }

		const ExecStmtList &getStmtList() const { return m_stmts; }

	private:
		ExecType							m_execType;
		exec::ExecKind						m_execKind;

		std::string							m_language;
		std::string							m_content;
		ExecStmtList						m_stmts;

};

} /* namespace pss */

#endif /* SRC_CLASSLIB_EXEC_H_ */
