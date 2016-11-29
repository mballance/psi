/*
 * BaseItemImpl.cpp
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
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#include "BaseItemImpl.h"

namespace psi {

BaseItemImpl::BaseItemImpl(IBaseItem::ItemType t) :
		m_type(t), m_parent(0) {
	// TODO Auto-generated constructor stub

}

BaseItemImpl::~BaseItemImpl() {
	// TODO Auto-generated destructor stub
}

IBaseItem::ItemType BaseItemImpl::getType() const {
	return m_type;
}

void BaseItemImpl::setType(IBaseItem::ItemType t) {
	m_type = t;
}


} /* namespace psi */
