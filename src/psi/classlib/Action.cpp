/*
 * Action.cpp
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
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "classlib/Action.h"

#include <stdio.h>
#include "classlib/TypeRegistry.h"

namespace psi {

Action::Action(
		Type 				*p,
		const std::string 	&name,
		Action				*super_type) : Type(Type::TypeAction, p, name),
				m_super_type(super_type) {

}

Action::~Action() {
	// TODO Auto-generated destructor stub
}

Action::Action(Type *p) : Type(Type::TypeAction, p, "") {
	// Unused constructor used by TypeRgy
}

void Action::pre_solve() {

}

void Action::post_solve() {

}

void Action::body() {

}

} /* namespace psi */
