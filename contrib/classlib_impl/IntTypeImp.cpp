/*
 * int_type.cpp
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
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#include "IntTypeImp.h"

namespace pss {

int_type::int_type(
		base_item 			*p,
		uint32_t			msb,
		uint32_t			lsb) :
	base_item(new IntTypeImp(this, p, msb, lsb)) { }

IntTypeImp::IntTypeImp(
		int_type				*master,
		base_item 			*p,
		uint32_t			msb,
		uint32_t			lsb) :
	NamedBaseItemImp(master, BaseItemImp::TypeInt, p),
	m_msb(msb), m_lsb(lsb), m_utils(this) { }

int_type::int_type(
		const std::string	&name,
		uint32_t			msb,
		uint32_t			lsb) :
	base_item(new IntTypeImp(this, name, msb, lsb)) { }

IntTypeImp::IntTypeImp(
		int_type				*master,
		const std::string	&name,
		uint32_t			msb,
		uint32_t			lsb) :
	NamedBaseItemImp(master, BaseItemImp::TypeInt, 0, name),
	m_msb(msb), m_lsb(lsb), m_utils(this) {
}

int_type::~int_type() { }

IntTypeImp::~IntTypeImp() { }

int64_t int_type::get() {
	return static_cast<IntTypeImp *>(impl())->get();
}

int64_t IntTypeImp::get() {
	return m_utils.getIntValue();
}

void int_type::set(int64_t v) {
	static_cast<IntTypeImp *>(impl())->set(v);
}

void IntTypeImp::set(int64_t v) {
	m_utils.setIntValue(v);
}

} /* namespace pss */
