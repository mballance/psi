/*
 * Model.cpp
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
 *
 *  Created on: Apr 25, 2016
 *      Author: ballance
 */

#include "classlib/Model.h"
#include "classlib/Scope.h"

#include <stdio.h>

namespace psi {

Model::Model() : BaseItem(BaseItem::Model, 0) {
}

Model::~Model() {
	// TODO Auto-generated destructor stub
}

Model *Model::global() {
	if (!m_global) {
		m_global = new Model();
	}
	return m_global;
}

void Model::push_scope(const Scope *p) {
	m_scope.push_back(p);
}

void Model::pop_scope() {
	const Scope *p = m_scope.back();
	m_scope.pop_back();
}

const std::vector<const Scope *> &Model::get_scope() const {
	return m_scope;
}

Model *Model::m_global = 0;

} /* namespace psi */
