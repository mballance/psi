/*
 * BoolImp.cpp
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

#include "BoolImp.h"
#include "ScopeImp.h"

namespace pss {

Bool::Bool(const Scope &p) : BaseItem(new BoolImp(this, p.impl()->parent())) { }

BoolImp::BoolImp(Bool *master, BaseItem *p) :
		NamedBaseItemImp(master, BaseItemImp::TypeBool, p) { }

Bool::Bool(const std::string &name) : BaseItem(new BoolImp(this, name)) { }

BoolImp::BoolImp(Bool *master, const std::string &name) :
		NamedBaseItemImp(master, BaseItemImp::TypeBool, 0, name) { }

Bool::~Bool() {

}

BoolImp::~BoolImp() {
	// TODO Auto-generated destructor stub
}

bool Bool::get() {
	return static_cast<BoolImp *>(impl())->get();
}

bool BoolImp::get() {
	// TODO:
	return false;
}

void Bool::set(bool v) {
	static_cast<BoolImp *>(impl())->set(v);
}

void BoolImp::set(bool v) {
	// TODO:
}

} /* namespace pss */
