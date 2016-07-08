/*
 * Struct.cpp
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

#include "classlib/Struct.h"
#include "classlib/Model.h"
#include "classlib/Scope.h"

namespace psi {

Struct::Struct(const Scope &p) : NamedBaseItem(BaseItem::TypeStruct, p.parent()),
				m_structType(Struct::Base), m_super(0) {
	setName(Model::global()->getActiveTypeName(this));
}

Struct::Struct(Struct::StructType t, BaseItem *p) :
				NamedBaseItem(BaseItem::TypeStruct, p),
				m_structType(t), m_super(0) {
	// TODO: determine super-struct information
//	m_super = super_type;
}

Struct::~Struct() {
	// TODO Auto-generated destructor stub
}

void Struct::pre_solve() {

}

void Struct::post_solve() {

}

void Struct::body() {

}

} /* namespace psi */
