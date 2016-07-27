/*
 * BitTypeImpl.cpp
 *
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

#include "BitTypeImpl.h"

namespace psi {

BitType::BitType(
		BaseItem				*p,
		uint32_t				msb,
		uint32_t				lsb) : BaseItem(new BitTypeImpl(this, p, msb, lsb)) { }

BitTypeImpl::BitTypeImpl(
		BitType					*master,
		BaseItem				*p,
		uint32_t				msb,
		uint32_t				lsb) :
	NamedBaseItemImpl(master, BaseItemImpl::TypeBit, p), m_msb(msb), m_lsb(lsb) { }

BitType::BitType(
		const std::string		&name,
		uint32_t				msb,
		uint32_t				lsb) : BaseItem(new BitTypeImpl(this, name, msb, lsb)) { }

BitTypeImpl::BitTypeImpl(
		BitType					*master,
		const std::string		&name,
		uint32_t				msb,
		uint32_t				lsb) : NamedBaseItemImpl(
				master, BaseItemImpl::TypeBit, 0, name), m_msb(msb), m_lsb(lsb) {
}

BitTypeImpl::~BitTypeImpl() {
	// TODO Auto-generated destructor stub
}

uint64_t BitTypeImpl::get() {
	// TODO:
	return 0;
}

uint64_t BitType::get() {
	return static_cast<BitTypeImpl *>(impl())->get();
}

void BitTypeImpl::set(uint64_t v) {
	// TODO:
}

void BitType::set(uint64_t v) {
	static_cast<BitTypeImpl *>(impl())->set();
}

} /* namespace psi */
