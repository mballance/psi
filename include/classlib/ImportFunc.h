/*
 *
 * ImportFunc.h
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

#ifndef INCLUDED_IMPORT_H
#define INCLUDED_IMPORT_H
#include <string>

#include "classlib/Expr.h"
#include "classlib/BaseItem.h"
#include "classlib/ExecImportCallStmt.h"
#include "classlib/MethodParamList.h"

namespace pss {

class ImportFunc : public BaseItem {

	public:

		ImportFunc(
				BaseItem 				*p,
				const std::string 		&name,
				const MethodParamList	&plist);

		ImportFunc(
				BaseItem 				*p,
				const std::string 		&name,
				const BaseItem 			&ret,
				const MethodParamList	&plist);

		virtual ~ImportFunc();

		ExecImportCallStmt operator()(const ExprList &plist);

#ifdef PSS_HAVE_CXX_11

		template<typename... I> ExecImportCallStmt operator()(const I&... items) {
			return ExecImportCallStmt(*this, ExprList::mklist(items...));
		}

#endif

		ExecImportCallStmt operator()();
};


} /* namespace pss */

#endif /* SRC_CLASSLIB_IMPORT_H_ */
