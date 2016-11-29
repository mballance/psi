/*
 * ChandleType.cpp
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

ChandleType::ChandleType(const Scope &p) :
		BaseItem(new ChandleTypeImpl(this, 0)) { }

ChandleTypeImpl::ChandleTypeImpl(ChandleType *master, BaseItem *p) :
		NamedBaseItemImp(master, BaseItemImp::TypeChandle, p),
		m_utils(this) { }

ChandleType::ChandleType(const std::string &name) :
		BaseItem(new ChandleTypeImpl(this, name)) { }

ChandleTypeImpl::ChandleTypeImpl(ChandleType *master, const std::string &name) :
		NamedBaseItemImp(master, BaseItemImp::TypeChandle, 0, name),
		m_utils(this) { }


ChandleType::~ChandleType() {
	// TODO Auto-generated destructor stub
}

ChandleTypeImpl::~ChandleTypeImpl() {
	// TODO Auto-generated destructor stub
}

void *ChandleType::get() {
	return static_cast<ChandleTypeImpl *>(impl())->get();
}

void *ChandleTypeImpl::get() {
	return m_utils.getChandleValue();
}

void ChandleTypeImpl::set(void *v) {
	m_utils.setChandleValue(v);
}

void ChandleType::set(void *v) {
	static_cast<ChandleTypeImpl *>(impl())->set(v);
}

} /* namespace pss */
