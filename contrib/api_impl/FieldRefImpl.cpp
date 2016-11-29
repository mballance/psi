/*
 * FieldRefImpl.cpp
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
 *  Created on: May 9, 2016
 *      Author: ballance
 */

#include "../api_impl/FieldRefImpl.h"

namespace psi {

FieldRefImpl::FieldRefImpl(const std::vector<IField *> &field_path) :
		m_field_path(field_path) {
	// TODO Auto-generated constructor stub

}

FieldRefImpl::FieldRefImpl(IField *field_path) {
	m_field_path.push_back(field_path);
}

FieldRefImpl::~FieldRefImpl() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
