/*
 * ConstraintExpr.h
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
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#ifndef IMPL_CONSTRAINTEXPRIMPL_H_
#define IMPL_CONSTRAINTEXPRIMPL_H_
#include "api/IConstraintExpr.h"
#include "BaseItemImpl.h"

using namespace psi_api;

namespace psi {

class ConstraintExprImpl:
		public virtual IConstraintExpr,
		public virtual BaseItemImpl {
public:

	ConstraintExprImpl(IExpr *expr);

	virtual ~ConstraintExprImpl();

	virtual ConstraintType getConstraintType() const { return IConstraint::ConstraintType_Expr; }

	virtual IExpr *getExpr() const { return m_expr; }

private:

	IExpr					*m_expr;

};

} /* namespace psi */

#endif /* IMPL_CONSTRAINTEXPRIMPL_H_ */
