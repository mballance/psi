/*
 * ExecImp.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 *  Created on: Apr 29, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_EXEC_IMP_H
#define INCLUDED_EXEC_IMP_H

#include <string>

#include "classlib/Exec.h"
#include "BaseItemImp.h"

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
			Exec						*master,
			BaseItem					*p,
			Exec::ExecKind 				kind,
			const std::string 			&language,
			const std::string 			&content);

		ExecImp(
			Exec						*master,
			ExtendItem					*p,
			Exec::ExecKind 				kind,
			const std::string 			&language,
			const std::string 			&content);

		ExecImp(
			Exec						*master,
			BaseItem					*p,
			Exec::ExecKind 				kind,
			const ExprList				&stmts);

		ExecImp(
			Exec						*master,
			ExtendItem					*p,
			Exec::ExecKind				kind,
			const ExprList				&stmts);

		/**
		 * Inline exec block that activates the appropriate
		 * hook method in the containing declaration
		 */
		ExecImp(
			Exec							*master,
			BaseItem						*p,
			Exec::ExecKind					kind);

		virtual ~ExecImp();

		inline Exec::ExecKind getExecKind() const {
			return m_execKind;
		}

		inline ExecType getExecType() const {
			return m_execType;
		}

		const std::string &getLanguage() const { return m_language; }

		const std::string &getTargetTemplate() const { return m_content; }

	private:
		ExecType							m_execType;
		Exec::ExecKind						m_execKind;

		std::string							m_language;
		std::string							m_content;
		ExprList							m_stmts;

};

} /* namespace pss */

#endif /* SRC_CLASSLIB_EXEC_H_ */
