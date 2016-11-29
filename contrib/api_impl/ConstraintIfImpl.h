/*
 * ConstraintIfImpl.h
 *
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

#ifndef IMPL_CONSTRAINTIFIMPL_H_
#define IMPL_CONSTRAINTIFIMPL_H_
#include "api/IConstraintIf.h"
#include "BaseItemImpl.h"

using namespace psi_api;

namespace psi {

class ConstraintIfImpl :
		public virtual IConstraintIf,
		public virtual BaseItemImpl {
public:
	ConstraintIfImpl(IExpr *cond, IConstraint *true_c, IConstraint *false_c);

	virtual ~ConstraintIfImpl();

	virtual ConstraintType getConstraintType() const { return IConstraint::ConstraintType_If; }

	virtual IExpr *getCond() const { return m_cond; }

	virtual IConstraint *getTrue() const { return m_true; }

	virtual IConstraint *getFalse() const { return m_false; }

private:

	IExpr					*m_cond;
	IConstraint				*m_true;
	IConstraint				*m_false;

};

} /* namespace psi */

#endif /* IMPL_CONSTRAINTIFIMPL_H_ */
