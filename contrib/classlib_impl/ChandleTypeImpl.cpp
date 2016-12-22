/*
 * chandle_type.cpp
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
 *
 *  Created on: Apr 29, 2016
 *      Author: ballance
 */

#include "ChandleTypeImpl.h"

namespace pss {

chandle_type::chandle_type(const scope &p) :
		base_item(new ChandleTypeImpl(this, 0)) { }

ChandleTypeImpl::ChandleTypeImpl(chandle_type *master, base_item *p) :
		NamedBaseItemImp(master, BaseItemImp::TypeChandle, p),
		m_utils(this) { }

chandle_type::chandle_type(const std::string &name) :
		base_item(new ChandleTypeImpl(this, name)) { }

ChandleTypeImpl::ChandleTypeImpl(chandle_type *master, const std::string &name) :
		NamedBaseItemImp(master, BaseItemImp::TypeChandle, 0, name),
		m_utils(this) { }


chandle_type::~chandle_type() {
	// TODO Auto-generated destructor stub
}

ChandleTypeImpl::~ChandleTypeImpl() {
	// TODO Auto-generated destructor stub
}

void *chandle_type::get() {
	return static_cast<ChandleTypeImpl *>(impl())->get();
}

void *ChandleTypeImpl::get() {
	return m_utils.getChandleValue();
}

void ChandleTypeImpl::set(void *v) {
	m_utils.setChandleValue(v);
}

void chandle_type::set(void *v) {
	static_cast<ChandleTypeImpl *>(impl())->set(v);
}

} /* namespace pss */
