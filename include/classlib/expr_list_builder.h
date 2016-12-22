/*
 * expr_list_builder.h
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
 *  Created on: Jun 10, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_EXPR_LIST_BUILDER_H
#define INCLUDED_EXPR_LIST_BUILDER_H
#include <vector>

#include "classlib/pss_types.h"

namespace pss {

class expr;
class ExprListBuilderImp;
class expr_list_builder {
public:

	expr_list_builder();

#ifdef PSS_HAVE_CXX_11
	expr_list_builder(std::initializer_list<expr> l) : 
		expr_list_builder(std::vector<expr>(l)) { }
#endif

	expr_list_builder(const std::vector<expr> &l);

	expr_list_builder(const expr &e1, const expr &e2);

	expr_list_builder(const expr &e1, const expr_list_builder &e2);

	virtual ~expr_list_builder();

	expr_list_builder &operator,(const expr &rhs);

	expr_list_builder &operator,(const expr_list_builder &rhs);

	void add(const expr &e);

	void add(const expr_list_builder &l);

	ExprListBuilderImp &imp() const { return *m_imp; }

private:
	ExprListBuilderImp							*m_imp;

};

} /* namespace pss */

#endif /* SRC_PSI_CLASSLIB_EXPRLISTBUILDER_H_ */
