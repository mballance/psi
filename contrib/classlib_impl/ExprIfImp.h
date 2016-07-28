/*
 * ExprIfImp.h
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

#ifndef SRC_PSI_CLASSLIB_EXPRCOREIF_H_
#define SRC_PSI_CLASSLIB_EXPRCOREIF_H_
#include "ExprCore.h"

namespace psi {

class ExprIfImp : public ExprCore {
public:

	ExprIfImp(const Expr &cond, const Expr &true_expr);

	ExprIfImp(const Expr &cond, const Expr &true_expr, const Expr &false_expr);

	virtual ~ExprIfImp();

	const ExprImp &getCond() const { return m_lhs; }

	const ExprImp &getTrue() const { return m_rhs; }

	const Expr &getFalse() const { return m_false_stmt; }

protected:

	Expr					m_false_stmt;
};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_EXPRCOREIF_H_ */
