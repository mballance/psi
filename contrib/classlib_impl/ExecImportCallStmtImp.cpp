/*
 * ExecImportCallStmtImp.cpp
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

#include "ExecImportCallStmtImp.h"

namespace pss {

exec_import_call_stmt::exec_import_call_stmt(
		const import_func		&imp,
		const expr_list			&plist) : exec_stmt(new ExecImportCallStmtImp(imp, plist)) { }

ExecImportCallStmtImp::ExecImportCallStmtImp(
		const import_func		&imp,
		const expr_list			&plist) :
				ExecStmtImp(StmtType_Call), m_imp(imp), m_plist(plist) { }

ExecImportCallStmtImp::~ExecImportCallStmtImp() {
	// TODO Auto-generated destructor stub
}

} /* namespace pss */
