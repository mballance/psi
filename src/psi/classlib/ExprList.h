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
#include "classlib/Expr.h"
#include "classlib/ExprImportCall.h"

namespace psi {

class ExprList : public Expr {
	public:

		ExprList();

		ExprList(const SharedPtr<ExprCore> &ptr);

		ExprList(const Expr &e, const Expr &e2);

		ExprList(const Expr &e);

		ExprList(Type &t);

		ExprList(int v);

		virtual ~ExprList();

		ExprList operator,(const Expr &rhs);

//		ExprList operator,(const ExprImportCall &rhs);

//		ExprList operator,(const Type &rhs);

	private:

};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_EXPRLIST_H_ */
