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

namespace psi {

class ExecImp : public BaseItemImp {

	public:
		enum ExecKind {
			Declaration,
			Body,
			PreSolve,
			PostSolve
		};
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
			ExecKind 					kind,
			const std::string 			&language,
			const std::string 			&content);

		ExecImp(
			Exec						*master,
			ExtendItem					*p,
			ExecKind 					kind,
			const std::string 			&language,
			const std::string 			&content);

		ExecImp(
			Exec						*master,
			BaseItem					*p,
			ExecKind 					kind,
			const ExprList				&stmts);

		ExecImp(
			Exec						*master,
			ExtendItem					*p,
			ExecKind 					kind,
			const ExprList				&stmts);

		/**
		 * Inline exec block that activates the appropriate
		 * hook method in the containing declaration
		 */
		ExecImp(
			Exec							*master,
			BaseItem						*p,
			ExecKind						kind,
			const std::vector<BaseItem *>	&write_vars);

#ifdef PSI_HAVE_CXX_11
		ExecImp(
			BaseItem								*p,
			ExecKind								kind,
			std::initializer_list<BaseItem>			write_vars) :
				BaseItem(BaseItem::TypeExec, p),
				m_execType(Inline),
				m_execKind(kind) {
			// TODO: save write variables
//			std::vector<BaseItem *> ptr_v;
//
//			for (std::initializer_list<BaseItem>::const_iterator it=write_vars.begin();
//					it!=write_vars.end(); it++) {
//				ptr_v.
//
//			}
		}
#endif

		virtual ~ExecImp();


		inline ExecKind getExecKind() const {
			return m_execKind;
		}

		inline ExecType getExecType() const {
			return m_execType;
		}

		const std::string &getLanguage() const { return m_language; }

		const std::string &getTargetTemplate() const { return m_content; }

	private:
		ExecType							m_execType;
		ExecKind							m_execKind;

		std::string							m_language;
		std::string							m_content;
		ExprList							m_stmts;

};

} /* namespace psi */

#endif /* SRC_CLASSLIB_EXEC_H_ */
