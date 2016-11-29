/*
 * Exec.h
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

#ifndef INCLUDED_EXEC_H
#define INCLUDED_EXEC_H

#include <string>

#include "classlib/BaseItem.h"
#include "classlib/Types.h"
#include "classlib/ExecStmtList.h"

namespace pss {

class ImportCall;
class ExtendItem;
class ExecStmtList;

class Exec : public BaseItem {

	public:
		enum ExecKind {
			Declaration,
			Body,
			PreSolve,
			PostSolve
		};

	public:

		Exec(
			BaseItem								*p,
			ExecKind 								kind,
			const std::string 						&language,
			const std::string 						&content);

		Exec(
			ExtendItem								*p,
			ExecKind 								kind,
			const std::string 						&language,
			const std::string 						&content);

		Exec(
			BaseItem								*p,
			ExecKind 								kind,
			const ExecStmtList						&stmts);

		Exec(
			ExtendItem								*p,
			ExecKind 								kind,
			const ExecStmtList						&stmts);

		/**
		 * Inline exec block that activates the appropriate
		 * hook method
		 */
		Exec(
			BaseItem								*p,
			ExecKind								kind);

#ifdef PSS_HAVE_CXX_11
//		Exec(
//			BaseItem								*p,
//			ExecKind								kind,
//			std::initializer_list<BaseItem>			write_vars) :
//				BaseItem(BaseItem::TypeExec, p),
//				m_execType(Inline),
//				m_execKind(kind) {
//			// TODO: save write variables
////			std::vector<BaseItem *> ptr_v;
////
////			for (std::initializer_list<BaseItem>::const_iterator it=write_vars.begin();
////					it!=write_vars.end(); it++) {
////				ptr_v.
////
////			}
//		}
#endif

		virtual ~Exec();


};

} /* namespace pss */

#endif /* SRC_CLASSLIB_EXEC_H_ */
