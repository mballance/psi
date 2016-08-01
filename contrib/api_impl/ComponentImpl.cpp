/*
 * ComponentImpl.cpp
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
 *  Created on: May 3, 2016
 *      Author: ballance
 */

#include "../api_impl/ComponentImpl.h"

#include "../api_impl/FieldImpl.h"

namespace psi {

ComponentImpl::ComponentImpl(const std::string &name) :
		m_parent(0), m_name(name) {
	// TODO Auto-generated constructor stub

}

ComponentImpl::~ComponentImpl() {
	// TODO Auto-generated destructor stub
}

IBaseItem *ComponentImpl::clone() {
	// TODO: implement clone
	return 0;
}

const std::string &ComponentImpl::getName() const {
	return m_name;
}

const std::vector<IBaseItem *> &ComponentImpl::getItems() const {
	return m_children;
}

void ComponentImpl::add(IBaseItem *it) {
	it->setParent(this);
	m_children.push_back(it);
}

/**
 * Locates and returns the named field. Returns 0 if
 * the named field does not exist
 */
IField *ComponentImpl::getField(const std::string &name) {
	IField *ret = 0;
	std::vector<IBaseItem *>::const_iterator it;

	for (it=m_children.begin(); it!=m_children.end(); it++) {
		if ((*it)->getType() == IBaseItem::TypeField &&
				static_cast<FieldImpl *>(*it)->getName() == name) {
			ret = static_cast<FieldImpl *>(*it);
			break;
		}

	}

	return ret;
}

} /* namespace psi */
