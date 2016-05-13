/*
 * ConstraintIfImpl.h
 *
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

#ifndef IMPL_CONSTRAINTIFIMPL_H_
#define IMPL_CONSTRAINTIFIMPL_H_
#include "api/IConstraintIf.h"

using namespace psi_api;

namespace psi {

class ConstraintIfImpl : public IConstraintIf {
public:
	ConstraintIfImpl(IExpr *cond, IConstraint *true_c, IConstraint *false_c);

	virtual ~ConstraintIfImpl();

	virtual ItemType getType() const { return IBaseItem::TypeConstraint; }

	virtual ConstraintType getConstraintType() const { return IConstraint::ConstraintType_If; }

	virtual IBaseItem *clone();

	virtual IBaseItem *getParent() const { return 0; }

	void setParent(IBaseItem *p) { }

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
