/*
 * ExprCoreIf.h
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

#ifndef INCLUDED_EXPR_CORE_IF_H
#define INCLUDED_EXPR_CORE_IF_H
#include "ExprCore.h"

namespace pss {

class ExprCoreIf : public ExprCore {
public:

	ExprCoreIf(const Expr &cond, const Expr &true_expr);

	ExprCoreIf(const Expr &cond, const Expr &true_expr, const Expr &false_expr);

	virtual ~ExprCoreIf();

	const ExprImp &getCond() const { return m_lhs; }

	const ExprImp &getTrue() const { return m_rhs; }

	const ExprImp &getFalse() const { return m_false_stmt; }

protected:

	ExprImp					m_false_stmt;
};

} /* namespace pss */

#endif /* SRC_PSI_CLASSLIB_EXPRCOREIF_H_ */
