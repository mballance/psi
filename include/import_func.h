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
#include <vector>

#include "prv/attr_item.h"
#include "prv/exec_import_call_stmt.h"
#include "prv/expr.h"

namespace pss {

class import_func : public vendor::import_func_impl {

	public:

		import_func(
				const std::string 					&name,
				const std::vector<prv::attr_item>	&plist);

#ifdef UNDEFINED
		import_func(
				const std::string 					&name,
				const base_item 					&ret,
				const std::vector<prv::attr_item>	&plist);
#endif

		virtual ~import_func();

		template<typename... I> prv::exec_import_call_stmt operator()(const I&... items);

		prv::exec_import_call_stmt operator()(const std::vector<prv::expr> &params);

		prv::exec_import_call_stmt operator()();
};


} /* namespace pss */

#endif /* SRC_CLASSLIB_IMPORT_H_ */
