/*
 * PackageImpl.cpp
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
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#include "PackageImpl.h"
#include "api/IAction.h"
#include "api/IStruct.h"

namespace psi {

PackageImpl::PackageImpl(const std::string &name, IBaseItem *parent) :
		m_name(name), m_parent(parent) {

}

PackageImpl::~PackageImpl() {
	// TODO Auto-generated destructor stub
}

IBaseItem *PackageImpl::clone() {
	// TODO: implement clone
	return 0;
}

void PackageImpl::add(IBaseItem *it) {
	it->setParent(this);
	m_children.push_back(it);
}

const std::vector<IAction *> PackageImpl::getActions() {
	return m_actions;
}

IAction *PackageImpl::findAction(const std::string &name) {
	std::vector<IAction *>::iterator it;

	for (it=m_actions.begin(); it!=m_actions.end(); it++) {
		if ((*it)->getName() == name) {
			return *it;
		}
	}

	return 0;
}

void PackageImpl::addAction(IAction *action) {
	m_actions.push_back(action);
}

const std::vector<IStruct *> PackageImpl::getStructs() {
	return m_structs;
}

IStruct *PackageImpl::findStruct(const std::string &name) {
	std::vector<IStruct *>::iterator it;

	for (it=m_structs.begin(); it!=m_structs.end(); it++) {
		if ((*it)->getName() == name) {
			return *it;
		}
	}

	return 0;
}

} /* namespace psi */
