/*
 * expr_list.h
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
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_EXPR_LIST_H
#define INCLUDED_EXPR_LIST_H
#include <vector>
#include "classlib/pss_types.h"
#include "classlib/expr.h"
#include "classlib/expr_list_builder.h"

namespace pss {

class ExprImp;
class expr_list : public expr {
	public:

		expr_list();

#ifdef PSS_HAVE_CXX_11
		expr_list(std::initializer_list<expr> l) : expr_list(expr_list_builder(l)) { }

		template<typename T, typename... R> static expr_list mklist(
				const T 			&item,
				const R&... 		rest) {
			expr_list_builder expr_l;
			_mklist(expr_l, item, rest...);
			return expr_list(expr_l);
		}
#endif

		expr_list(const expr &rhs);

		expr_list(const ExprImp &ptr);

		expr_list(const expr_list_builder &el);

		virtual ~expr_list();

		expr_list_builder operator,(const expr &rhs);

	private:

#ifdef PSS_HAVE_CXX_11
		template <typename T, typename... R> static void _mklist(
				expr_list_builder			&expr_l,
				const T					&item,
				const R&...				rest) {
			expr_l.add(item);
			_mklist(expr_l, rest...);
		}

		static void _mklist(expr_list_builder	&expr_l) { }
#endif


};

} /* namespace pss */

#endif /* SRC_PSI_CLASSLIB_EXPRLIST_H_ */
