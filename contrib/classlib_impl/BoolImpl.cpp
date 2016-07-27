/*
 * BoolImpl.cpp
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
 *  Created on: Apr 28, 2016
 *      Author: ballance
 */

#include "BoolImpl.h"

namespace psi {

Bool::Bool(const BaseItem *p) : BaseItem(new BoolImpl(this, p)) { }

BoolImpl::BoolImpl(Bool *master, BaseItem *p) :
		NamedBaseItemImpl(master, BaseItemImpl::TypeBool, p) { }

Bool::Bool(const std::string &name) : BaseItem(new BoolImpl(this, name)) { }

BoolImpl::BoolImpl(Bool *master, const std::string &name) :
		NamedBaseItemImpl(master, BaseItem::TypeBool, 0, name) { }

Bool::~Bool() {

}

BoolImpl::~BoolImpl() {
	// TODO Auto-generated destructor stub
}

bool Bool::get() {
	return static_cast<BoolImpl *>(impl())->get();
}

bool BoolImpl::get() {
	// TODO:
	return false;
}

void Bool::set(bool v) {
	static_cast<BoolImpl *>(impl())->set();
}

void BoolImpl::set(bool v) {
	// TODO:
}

} /* namespace psi */
