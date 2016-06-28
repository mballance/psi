/*
 * ExprList.cpp
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#include <vector>
#include "ExprList.h"
#include "ExprCoreList.h"
#include <stdio.h>

namespace psi {

ExprList::ExprList() : Expr(new ExprCoreList()) { }

ExprList::ExprList(const Expr &e) : Expr(new ExprCoreList()) {
	ExprCoreList *c_t = static_cast<ExprCoreList *>(m_core.ptr());
	c_t->m_exprList.push_back(e.getCore());
}

ExprList::ExprList(const SharedPtr<ExprCore> &ptr) : Expr(ptr) { }

ExprList::ExprList(const ExprListBuilder &el) : Expr(new ExprCoreList()) {
	ExprCoreList *c_t = static_cast<ExprCoreList *>(m_core.ptr());
	traverse_expr_builder(c_t, el);
}

//ExprList::ExprList(Type &t) : Expr(new ExprCoreList(Expr(t))) { }

ExprList::~ExprList() { }

ExprListBuilder ExprList::operator,(const Expr &rhs) {
	return ExprListBuilder(*this, rhs);
}

const std::vector<SharedPtr<ExprCore> > &ExprList::getExprList() const {
	return static_cast<ExprCoreList *>(m_core.ptr())->m_exprList;
}

void ExprList::append(const Expr &e) {
	std::vector<SharedPtr<ExprCore> > &l = static_cast<ExprCoreList *>(m_core.ptr())->m_exprList;
	l.push_back(e.getCore());
}

void ExprList::traverse_expr_builder(ExprCoreList *c_t, const ExprListBuilder &el) {
	if (el.getBuilderList().size() > 0) {
		// List of builders. Must convert each to an ExprCoreList
		// and add it to the list we're building
		std::vector<ExprListBuilder>::const_iterator it;

		for (it=el.getBuilderList().begin(); it!=el.getBuilderList().end(); it++) {
			ExprCoreList *c_tp = new ExprCoreList();

			traverse_expr_builder(c_tp, *it);

			c_t->m_exprList.push_back(SharedPtr<ExprCore>(c_tp));
		}
	} else {
		// List of CoreExpr. Add to the current list
		std::vector<SharedPtr<ExprCore> >::const_iterator it;
		for (it=el.getList().begin(); it!=el.getList().end(); it++) {
			c_t->m_exprList.push_back(*it);
		}
	}

}

} /* namespace psi */
