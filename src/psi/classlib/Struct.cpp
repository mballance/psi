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

#include "classlib/TypeRegistry.h"

namespace psi {

Struct::Struct() : Type(Type::TypeStruct, "", nullptr),
		m_structType(Struct::Base),
		m_superRef(Type::TypeRef, nullptr), m_super(nullptr) { }

Struct::Struct(
		const std::string 	&name,
		Type 				*p,
		Struct 				&super_type) :
				Type(Type::TypeStruct, name, (p==nullptr)?TypeRegistry::global():p),
				m_structType(Struct::Base),
				m_superRef(Type::TypeRef, nullptr) {

	if (&super_type == &None) {
		m_super = nullptr;
	} else {
		m_super = &super_type;
	}
}

Struct::Struct(
		const std::string 	&name,
		Type 				*p,
		const std::string	&super_name) :
				Type(Type::TypeStruct, name, (p==nullptr)?TypeRegistry::global():p),
				m_structType(Struct::Base),
				m_superRef(Type::TypeRef, super_name, nullptr),
				m_super(&m_superRef) {
}

Struct::Struct(
		Struct::StructType	t,
		const std::string 	&name,
		Type 				*p,
		Struct 				&super_type) :
				Type(Type::TypeStruct, name, (p==nullptr)?TypeRegistry::global():p),
				m_structType(t),
				m_superRef(Type::TypeRef, nullptr) {

	if (&super_type == &None) {
		m_super = nullptr;
	} else {
		m_super = &super_type;
	}
}

Struct::Struct(
		Struct::StructType	t,
		const std::string 	&name,
		Type 				*p,
		const std::string	&super_name) :
				Type(Type::TypeStruct, name, (p==nullptr)?TypeRegistry::global():p),
				m_structType(t),
				m_superRef(Type::TypeRef, super_name, nullptr),
				m_super(&m_superRef) {
}

Struct::~Struct() {
	// TODO Auto-generated destructor stub
}

Struct Struct::None; // = Struct("", nullptr);

} /* namespace psi */
