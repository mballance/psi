/*
 * repeat.h
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
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_REPEAT_H
#define INCLUDED_REPEAT_H
#include "classlib/pss_types.h"
#include "classlib/expr.h"
#include "classlib/expr_list.h"
#include "classlib/expr_list_builder.h"

namespace pss {

class repeat: public expr {
public:

#ifdef PSS_HAVE_CXX_11
	template<typename... I> repeat(const expr &cond, const I&... items) :
		repeat(cond, expr_list::mklist(items...)) { }
#endif

	repeat(const expr &cond, const expr_list &body);

	virtual ~repeat();

	expr_list_builder operator,(const expr &rhs);

	expr_list_builder operator,(const expr_list_builder &rhs);

};

} /* namespace pss */

#endif /* SRC_PSI_CLASSLIB_REPEAT_H_ */
