/*
 * FieldImpl.cpp
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
 *  Created on: May 5, 2016
 *      Author: ballance
 */

#include "FieldImpl.h"

namespace psi {

FieldImpl::FieldImpl(
		const std::string		&name,
		IBaseItem				*field_type,
		IField::FieldAttr		attr,
		IExpr					*array_dim) :
				BaseItemImpl(IBaseItem::TypeField),
				NamedItemImpl(name), m_field_type(field_type),
				m_attr(attr), m_array_dim(array_dim) { }

FieldImpl::~FieldImpl() {
	// TODO Auto-generated destructor stub
}


} /* namespace psi */
