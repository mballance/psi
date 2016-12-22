/*
 * ExprListImp.cpp
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

#include "classlib/expr_list.h"
#include "ExprCoreList.h"
#include "ExprImp.h"
#include "ExprListBuilderImp.h"

namespace pss {

void traverse_expr_builder(ExprCoreList *c_t, const ExprListBuilderImp &el);

expr_list::expr_list() : expr(ExprImp(new ExprCoreList())) {

}

expr_list::~expr_list() {

}

expr_list::expr_list(const expr &rhs) : expr(ExprImp(new ExprCoreList())) {
	ExprCoreList *c_t = static_cast<ExprCoreList *>(m_core->ptr());
	c_t->m_exprList.push_back(rhs.imp());
}

expr_list::expr_list(const ExprImp &rhs) : expr(rhs) { }

expr_list::expr_list(const expr_list_builder &el) : expr(ExprImp(new ExprCoreList())) {
	ExprCoreList *c_t = static_cast<ExprCoreList *>(m_core->ptr());
	traverse_expr_builder(c_t, el.imp());
}

void traverse_expr_builder(ExprCoreList *c_t, const ExprListBuilderImp &el) {

	if (el.getBuilderList().size() > 0) {
		// List of builders. Must convert each to an ExprCoreList
		// and add it to the list we're building
		std::vector<ExprListBuilderImp>::const_iterator it;

		for (it=el.getBuilderList().begin(); it!=el.getBuilderList().end(); it++) {
			ExprCoreList *c_tp = new ExprCoreList();

			traverse_expr_builder(c_tp, *it);

			c_t->add(ExprImp(c_tp));
		}
	} else {
		// List of CoreExpr. Add to the current list
		std::vector<ExprImp>::const_iterator it;
		for (it=el.getList().begin(); it!=el.getList().end(); it++) {
			c_t->add((*it));
		}
	}
}


} /* namespace pss */
