/*
 * ExprList.h
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

#ifndef SRC_PSI_CLASSLIB_EXPRLIST_H_
#define SRC_PSI_CLASSLIB_EXPRLIST_H_
#include <vector>
#include "classlib/Types.h"
#include "classlib/Expr.h"
#include "classlib/ExprImportCall.h"
#include "classlib/ExprListBuilder.h"

namespace psi {

class ExprCoreList;
class ExprList : public Expr {
	public:

		ExprList();

#ifdef PSI_HAVE_CXX_11
		ExprList(std::initializer_list<Expr> l) : ExprList() {
			std::initializer_list<Expr>::const_iterator it;

			fprintf(stdout, "ExprList<initializer>\n");

			for (it=l.begin(); it!=l.end(); it++) {
				append(*it);
			}
		}
#endif

		ExprList(const SharedPtr<ExprCore> &ptr);

		ExprList(const ExprListBuilder &el);

		ExprList(const Expr &rhs);

//		ExprList(Type &t);

//		ExprList(int v);

		virtual ~ExprList();

		ExprListBuilder operator,(const Expr &rhs);

		const std::vector<SharedPtr<ExprCore> > &getExprList() const;

	private:

		void append(const Expr &e);

		void traverse_expr_builder(ExprCoreList *c_t, const ExprListBuilder &el);

};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_EXPRLIST_H_ */
