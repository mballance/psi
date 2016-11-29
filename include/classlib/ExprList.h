/*
 * ExprList.h
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
#include "classlib/Types.h"
#include "classlib/Expr.h"
#include "classlib/ExprListBuilder.h"

namespace pss {

class ExprImp;
class ExprList : public Expr {
	public:

		ExprList();

#ifdef PSS_HAVE_CXX_11
		ExprList(std::initializer_list<Expr> l) : ExprList(ExprListBuilder(l)) { }

		template<typename T, typename... R> static ExprList mklist(
				const T 			&item,
				const R&... 		rest) {
			ExprListBuilder expr_l;
			_mklist(expr_l, item, rest...);
			return ExprList(expr_l);
		}
#endif

		ExprList(const Expr &rhs);

		ExprList(const ExprImp &ptr);

		ExprList(const ExprListBuilder &el);

		virtual ~ExprList();

		ExprListBuilder operator,(const Expr &rhs);

	private:

#ifdef PSS_HAVE_CXX_11
		template <typename T, typename... R> static void _mklist(
				ExprListBuilder			&expr_l,
				const T					&item,
				const R&...				rest) {
			expr_l.add(item);
			_mklist(expr_l, rest...);
		}

		static void _mklist(ExprListBuilder	&expr_l) { }
#endif


};

} /* namespace pss */

#endif /* SRC_PSI_CLASSLIB_EXPRLIST_H_ */
