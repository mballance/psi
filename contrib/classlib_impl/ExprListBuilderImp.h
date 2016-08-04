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

#ifndef INCLUDED_EXPR_LIST_BUILDER_IMP_H
#define INCLUDED_EXPR_LIST_BUILDER_IMP_H
#include <vector>

#include "classlib/ExprListBuilder.h"
#include "ExprImp.h"

namespace pss {

class Expr;
class ExprImp;
class ExprListBuilderImp {
public:
	friend class ExprListBuilder;

	ExprListBuilderImp();

	ExprListBuilderImp(const std::vector<Expr> &l);

	ExprListBuilderImp(const Expr &e1, const Expr &e2);

	ExprListBuilderImp(const Expr &e1, const ExprListBuilder &e2);

	virtual ~ExprListBuilderImp();

	const std::vector<ExprImp>            &getList() const { return m_list; }
	const std::vector<ExprListBuilderImp> &getBuilderList() const { return m_builders; }

private:
	std::vector<ExprImp>					m_list;
	std::vector<ExprListBuilderImp>			m_builders;

};

} /* namespace pss */

#endif /* SRC_PSI_CLASSLIB_EXPRLISTBUILDER_H_ */
