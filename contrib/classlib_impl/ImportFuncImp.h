/*
 * import_func.h
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

#ifndef INCLUDED_IMPORT_IMP_H
#define INCLUDED_IMPORT_IMP_H
#include <string>

#include "classlib/import_func.h"
#include "NamedBaseItemImp.h"
#include "MethodParamListImp.h"

namespace pss {

class ImportFuncImp : public NamedBaseItemImp {

	public:

		ImportFuncImp(
				import_func					*master,
				base_item 				*p,
				const std::string 		&name,
				const method_param_list	&plist);

		ImportFuncImp(
				import_func					*master,
				base_item 				*p,
				const std::string 		&name,
				const base_item 			&ret,
				const method_param_list	&plist);

		virtual ~ImportFuncImp();

//		exec_import_call_stmt operator()(const expr_list &plist);
//
//		exec_import_call_stmt operator()();

		BaseItemImp *getReturnType() {
			return (m_have_ret)?m_ret.impl():0;
		}

		const method_param_list &getParameters() const { return m_parameters; }

	private:

		bool						m_have_ret;
		base_item					m_ret;
		method_param_list				m_parameters;

};


} /* namespace pss */

#endif /* SRC_CLASSLIB_IMPORT_H_ */
