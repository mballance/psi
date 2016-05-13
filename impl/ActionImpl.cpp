/*
 * ActionImpl.cpp
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

#include "ActionImpl.h"

namespace psi {

ActionImpl::ActionImpl(
		const std::string 	&name,
		IAction 			*super_type) :
		m_parent(0), m_name(name), m_super_type(super_type), m_graph(0) {

}

ActionImpl::~ActionImpl() {
	// TODO Auto-generated destructor stub
}

const std::string &ActionImpl::getName() const {
	return m_name;
}

const std::vector<IBaseItem *> &ActionImpl::getItems() const {
	return m_children;
}

IBaseItem *ActionImpl::clone() {
	// TODO: implement clone
	return 0;
}

void ActionImpl::add(IBaseItem *it) {
	it->setParent(this);
	m_children.push_back(it);
}

void ActionImpl::setGraph(IGraphStmt *graph) {
	m_graph = graph;
}


} /* namespace psi */
