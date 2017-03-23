/*
 * exec.h
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
#include "prv/exec_stmt.h"
#include "prv/attr_item.h"

namespace pss {

class exec : public vendor::exec_impl {

	public:
		enum ExecKind {
			Declaration,
			Body,
			PreSolve,
			PostSolve
		};

	public:

		exec(
			ExecKind 								kind,
			const std::string 						&language,
			const std::string 						&content);

		exec(
			ExecKind 								kind,
			const std::vector<exec_stmt>			&stmts);

		/**
		 * Inline exec block that activates the appropriate
		 * hook method
		 */
		exec(
			ExecKind								kind,
			const std::vector<prv::attr_item>		&write_vars);

#ifdef PSS_HAVE_CXX_11
//		exec(
//			base_item								*p,
//			ExecKind								kind,
//			std::initializer_list<base_item>			write_vars) :
//				base_item(base_item::TypeExec, p),
//				m_execType(Inline),
//				m_execKind(kind) {
//			// TODO: save write variables
////			std::vector<base_item *> ptr_v;
////
////			for (std::initializer_list<base_item>::const_iterator it=write_vars.begin();
////					it!=write_vars.end(); it++) {
////				ptr_v.
////
////			}
//		}
#endif

		virtual ~exec();


};

} /* namespace pss */

#endif /* SRC_CLASSLIB_EXEC_H_ */
