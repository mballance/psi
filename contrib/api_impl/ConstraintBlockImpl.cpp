/*
 * ConstraintBlockImpl.cpp
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

#include "ConstraintBlockImpl.h"

namespace psi {

ConstraintBlockImpl::ConstraintBlockImpl(const std::string &name) :
		BaseItemImpl(IBaseItem::TypeConstraint), NamedItemImpl(name) {

}

ConstraintBlockImpl::~ConstraintBlockImpl() {
	// TODO Auto-generated destructor stub
}

void ConstraintBlockImpl::add(IConstraint *c) {
	m_constraints.push_back(c);
}

void ConstraintBlockImpl::add(const std::vector<IConstraint *> &cl) {
	std::vector<IConstraint *>::const_iterator it;

	for (it=cl.begin(); it!=cl.end(); it++) {
		m_constraints.push_back(*it);
	}
}

} /* namespace psi */
