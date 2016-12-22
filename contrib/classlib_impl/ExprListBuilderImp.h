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
 *
 *  Created on: Jun 10, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_EXPR_LIST_BUILDER_IMP_H
#define INCLUDED_EXPR_LIST_BUILDER_IMP_H
#include <vector>

#include "classlib/expr_list_builder.h"
#include "ExprImp.h"

namespace pss {

class expr;
class ExprImp;
class ExprListBuilderImp {
public:
	friend class expr_list_builder;

	ExprListBuilderImp();

	ExprListBuilderImp(const std::vector<expr> &l);

	ExprListBuilderImp(const expr &e1, const expr &e2);

	ExprListBuilderImp(const expr &e1, const expr_list_builder &e2);

	virtual ~ExprListBuilderImp();

	const std::vector<ExprImp>            &getList() const { return m_list; }
	const std::vector<ExprListBuilderImp> &getBuilderList() const { return m_builders; }

private:
	std::vector<ExprImp>					m_list;
	std::vector<ExprListBuilderImp>			m_builders;

};

} /* namespace pss */

#endif /* SRC_PSI_CLASSLIB_EXPRLISTBUILDER_H_ */
