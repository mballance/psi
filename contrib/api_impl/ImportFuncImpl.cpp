/*
 * ImportFuncImpl.cpp
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
 *  Created on: Aug 11, 2016
 *      Author: ballance
 */

#include "ImportFuncImpl.h"

namespace psi {

ImportFuncImpl::ImportFuncImpl(
		const std::string				&name,
		IField							*ret,
		const std::vector<IField *>		&parameters) :
				BaseItemImpl(IBaseItem::TypeImportFunc),
				NamedItemImpl(name), m_ret(ret), m_parameters(parameters) {
	m_cb = 0;

}

ImportFuncImpl::~ImportFuncImpl() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi_api */
