/*
 * BitTypeImp.cpp
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
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "BitTypeImp.h"
#include "ActionImp.h"
#include "StructImp.h"
#include "ComponentImp.h"
#include "api/IModel.h"
#include "InlineExecUtil.h"

using namespace psi_api;

namespace pss {

bit_type::bit_type(
		base_item				*p,
		uint32_t				msb,
		uint32_t				lsb) : base_item(new BitTypeImp(this, p, msb, lsb)) { }

BitTypeImp::BitTypeImp(
		bit_type					*master,
		base_item				*p,
		uint32_t				msb,
		uint32_t				lsb) :
	NamedBaseItemImp(master, BaseItemImp::TypeBit, p), m_msb(msb), m_lsb(lsb),
	m_utils(this) { }

bit_type::bit_type(
		const std::string		&name,
		uint32_t				msb,
		uint32_t				lsb) : base_item(new BitTypeImp(this, name, msb, lsb)) { }

BitTypeImp::BitTypeImp(
		bit_type					*master,
		const std::string		&name,
		uint32_t				msb,
		uint32_t				lsb) : NamedBaseItemImp(
				master, BaseItemImp::TypeBit, 0, name), m_msb(msb), m_lsb(lsb),
				m_utils(this) {
}

bit_type::~bit_type() {
	// TODO Auto-generated destructor stub
}

BitTypeImp::~BitTypeImp() {
	// TODO Auto-generated destructor stub
}

uint64_t BitTypeImp::get() {
	return m_utils.getBitValue();
}

uint64_t bit_type::get() {
	return static_cast<BitTypeImp *>(impl())->get();
}

void BitTypeImp::set(uint64_t v) {
	m_utils.setBitValue(v);
}

void bit_type::set(uint64_t v) {
	static_cast<BitTypeImp *>(impl())->set(v);
}

} /* namespace pss */
