/*
 * BoolImp.cpp
 *
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
 *  Created on: Apr 28, 2016
 *      Author: ballance
 */

#include "BoolImp.h"
#include "ScopeImp.h"

namespace pss {

pss_bool::pss_bool(const Scope &p) : BaseItem(new BoolImp(this, p.impl()->parent())) { }

BoolImp::BoolImp(pss_bool *master, BaseItem *p) :
		NamedBaseItemImp(master, BaseItemImp::TypeBool, p),
		m_utils(this) { }

pss_bool::pss_bool(const std::string &name) : BaseItem(new BoolImp(this, name)) { }

BoolImp::BoolImp(pss_bool *master, const std::string &name) :
		NamedBaseItemImp(master, BaseItemImp::TypeBool, 0, name),
		m_utils(this) { }

pss_bool::~pss_bool() {

}

BoolImp::~BoolImp() {
	// TODO Auto-generated destructor stub
}

bool pss_bool::get() {
	return static_cast<BoolImp *>(impl())->get();
}

bool BoolImp::get() {
	return m_utils.getBoolValue();
}

void pss_bool::set(bool v) {
	static_cast<BoolImp *>(impl())->set(v);
}

void BoolImp::set(bool v) {
	m_utils.setBoolValue(v);
}

} /* namespace pss */
