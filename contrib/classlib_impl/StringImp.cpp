/*
 * pss_string.cpp
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

#include "StringImp.h"

namespace pss {

pss_string::pss_string(BaseItem *p) :
		BaseItem(new StringImp(this, p)) { }

StringImp::StringImp(pss_string *master, BaseItem *p) :
		NamedBaseItemImp(master, BaseItemImp::TypeString, p),
		m_utils(this) { }

pss_string::pss_string(const std::string &name) :
		BaseItem(new StringImp(this, name)) { }

StringImp::StringImp(pss_string *master, const std::string &name) :
		NamedBaseItemImp(master, BaseItemImp::TypeString, 0, name),
		m_utils(this) { }

pss_string::~pss_string() {
}

StringImp::~StringImp() {
	// TODO Auto-generated destructor stub
}

std::string pss_string::get() {
	// TODO:
	return static_cast<StringImp *>(impl())->get();
}

std::string StringImp::get() {
	return m_utils.getStringValue();
}

void pss_string::set(const std::string &v) {
	static_cast<StringImp *>(impl())->set(v);
}

void StringImp::set(const std::string &v) {
	m_utils.setStringValue(v);
}

} /* namespace pss */
