/*
 * ExecImportCallStmtImp.h
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

#ifndef CONTRIB_CLASSLIB_IMPL_EXECIMPORTCALLSTMTIMP_H_
#define CONTRIB_CLASSLIB_IMPL_EXECIMPORTCALLSTMTIMP_H_

#include "ExecStmtImp.h"
#include "classlib/import_func.h"
#include "classlib/expr_list.h"
#include "ImportFuncImp.h"

namespace pss {

class ExecImportCallStmtImp: public ExecStmtImp {
public:
	ExecImportCallStmtImp(
			const import_func		&imp,
			const expr_list			&plist
			);

	virtual ~ExecImportCallStmtImp();

	ImportFuncImp *getFunc() const { return static_cast<ImportFuncImp *>(m_imp.impl()); }

	expr_list &getParameterList() { return m_plist; }

private:
	import_func						m_imp;
	expr_list						m_plist;

};

} /* namespace pss */

#endif /* CONTRIB_CLASSLIB_IMPL_EXECIMPORTCALLSTMTIMP_H_ */
