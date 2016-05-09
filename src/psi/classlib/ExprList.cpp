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

#include "ExprList.h"
#include "ExprCoreList.h"
#include <stdio.h>

namespace psi {

ExprList::ExprList() : Expr(new ExprCoreList()) { }

ExprList::ExprList(const SharedPtr<ExprCore> &ptr) : Expr(ptr) { }

ExprList::ExprList(const Expr &e1, const Expr &e2) : Expr(new ExprCoreList(e1, e2)) { }

ExprList::ExprList(const Expr &e) : Expr(new ExprCoreList(e)) { }

ExprList::ExprList(const Type &t) : Expr(new ExprCoreList(Expr(t))) {

}

ExprList::~ExprList() { }

ExprList ExprList::operator,(const Expr &rhs) {
	ExprCoreList *c_t = static_cast<ExprCoreList *>(m_core.ptr());

	if (rhs.getCore().ptr()) {
		if (rhs.getOp() == Expr::List) {
			ExprCoreList *rhs_c = static_cast<ExprCoreList *>(rhs.getCorePtr());
			std::vector<SharedPtr<ExprCore> >::const_iterator it;
			for (it=rhs_c->getExprList().begin(); it!=rhs_c->getExprList().end(); it++) {
				c_t->m_exprList.push_back((*it));
			}
		} else {
			c_t->m_exprList.push_back(rhs.getCore());
		}
	}
	return ExprList(m_core); // Hand off our shared pointer
}

//ExprList ExprList::operator,(const Type &rhs) {
//	ExprCoreList *c_t = static_cast<ExprCoreList *>(m_core.ptr());
//	fprintf(stdout, "ExprList::operator: Type rhs\n");
//	return ExprList(m_core);
//}


} /* namespace psi */
