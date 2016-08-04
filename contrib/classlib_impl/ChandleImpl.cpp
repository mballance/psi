/*
 * Chandle.cpp
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
 *  Created on: Apr 29, 2016
 *      Author: ballance
 */

#include "ChandleImpl.h"

namespace pss {

Chandle::Chandle(BaseItem *p) :
		BaseItem(new ChandleImpl(this, p)) { }

ChandleImpl::ChandleImpl(Chandle *master, BaseItem *p) :
		NamedBaseItemImp(master, BaseItemImp::TypeChandle, p) { }

Chandle::Chandle(const std::string &name) :
		BaseItem(new ChandleImpl(this, name)) { }

ChandleImpl::ChandleImpl(Chandle *master, const std::string &name) :
		NamedBaseItemImp(master, BaseItemImp::TypeChandle, 0, name) { }


Chandle::~Chandle() {
	// TODO Auto-generated destructor stub
}

ChandleImpl::~ChandleImpl() {
	// TODO Auto-generated destructor stub
}

void *Chandle::get() {
	return static_cast<ChandleImpl *>(impl())->get();
}

void *ChandleImpl::get() {
	// TODO:
	return 0;
}

void ChandleImpl::set(void *v) {
	// TODO:
}

void Chandle::set(void *v) {
	static_cast<ChandleImpl *>(impl())->set(v);
}

} /* namespace pss */
