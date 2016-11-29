/*
 * ExprCoreList.h
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

#ifndef INCLUDED_EXPR_CORE_LIST_H
#define INCLUDED_EXPR_CORE_LIST_H

#include <vector>
#include "ExprCore.h"

namespace pss {

class ExprList;
class ExprCoreList: public ExprCore {
	friend class ExprList;

public:

	ExprCoreList();

	ExprCoreList(const Expr &e);

	ExprCoreList(const Expr &e1, const Expr &e2);

	virtual ~ExprCoreList();

	void add(const Expr &e);

	void add(const ExprImp &e);

	const std::vector<ExprImp> &getExprList() const {
		return m_exprList;
	}

private:

	std::vector<ExprImp>			m_exprList;

};

} /* namespace pss */

#endif /* SRC_PSI_CLASSLIB_EXPRCORELIST_H_ */
