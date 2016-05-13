/*
 * ConstraintBlockImpl.h
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

#ifndef IMPL_CONSTRAINTBLOCKIMPL_H_
#define IMPL_CONSTRAINTBLOCKIMPL_H_
#include <string>
#include <vector>

#include "api/IConstraintBlock.h"

using namespace psi_api;

namespace psi {

class ConstraintBlockImpl: public IConstraintBlock {
public:
	ConstraintBlockImpl(const std::string &name);

	virtual ~ConstraintBlockImpl();

	virtual ItemType getType() const { return IBaseItem::TypeConstraint; }

	virtual ConstraintType getConstraintType() const { return IConstraint::ConstraintType_Block; }

	virtual IBaseItem *clone();

	virtual IBaseItem *getParent() const { return m_parent; }

	void setParent(IBaseItem *p) { m_parent = p; }

	virtual const std::string &getName() const { return m_name; }

	virtual void add(IConstraint *c);

	virtual void add(const std::vector<IConstraint *> &cl);

	virtual const std::vector<IConstraint *> &getConstraints() const { return m_constraints; }

private:
	IBaseItem								*m_parent;
	std::string								m_name;
	std::vector<IConstraint *>				m_constraints;

};

} /* namespace psi */

#endif /* IMPL_CONSTRAINTBLOCKIMPL_H_ */
