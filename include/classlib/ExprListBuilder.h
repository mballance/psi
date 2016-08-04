/*
 * ExprListBuilder.h
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
 *  Created on: Jun 10, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_EXPR_LIST_BUILDER_H
#define INCLUDED_EXPR_LIST_BUILDER_H
#include <vector>

#include "classlib/Types.h"

namespace pss {

class Expr;
class ExprListBuilderImp;
class ExprListBuilder {
public:

	ExprListBuilder();

#ifdef PSS_HAVE_CXX_11
	ExprListBuilder(std::initializer_list<Expr> l) : ExprListBuilder(std::vector<Expr>(l)) { }
//		std::initializer_list<Expr>::const_iterator it;
//
//		for (it=l.begin(); it!=l.end(); it++) {
//			m_list.push_back((*it).getCore());
//		}
//	}
#endif

	ExprListBuilder(const std::vector<Expr> &l);

	ExprListBuilder(const Expr &e1, const Expr &e2);

	ExprListBuilder(const Expr &e1, const ExprListBuilder &e2);

	virtual ~ExprListBuilder();

	ExprListBuilder &operator,(const Expr &rhs);

	ExprListBuilder &operator,(const ExprListBuilder &rhs);

	ExprListBuilderImp &imp() const { return *m_imp; }

private:
	ExprListBuilderImp							*m_imp;

};

} /* namespace pss */

#endif /* SRC_PSI_CLASSLIB_EXPRLISTBUILDER_H_ */
