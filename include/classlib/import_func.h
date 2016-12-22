/*
 *
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

#ifndef INCLUDED_IMPORT_H
#define INCLUDED_IMPORT_H
#include <string>

#include "classlib/expr.h"
#include "classlib/base_item.h"
#include "classlib/exec_import_call_stmt.h"
#include "classlib/method_param_list.h"
#include "classlib/expr_list.h"

namespace pss {

class import_func : public base_item {

	public:

		import_func(
				base_item 				*p,
				const std::string 		&name,
				const method_param_list	&plist);

		import_func(
				base_item 				*p,
				const std::string 		&name,
				const base_item 			&ret,
				const method_param_list	&plist);

		virtual ~import_func();

		exec_import_call_stmt operator()(const expr_list &plist);

#ifdef PSS_HAVE_CXX_11

		template<typename... I> exec_import_call_stmt operator()(const I&... items) {
			return exec_import_call_stmt(*this, expr_list::mklist(items...));
		}

#endif

		exec_import_call_stmt operator()();
};


} /* namespace pss */

#endif /* SRC_CLASSLIB_IMPORT_H_ */
