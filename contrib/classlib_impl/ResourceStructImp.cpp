/*
 * resource_struct.cpp
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

#include "ResourceStructImp.h"
#include "ScopeImp.h"

namespace pss {

resource_struct::resource_struct(const Scope &p) :
		pss_struct(new ResourceStructImp(this, p.impl())),
		instance_id("instance_id")
		{ }

ResourceStructImp::ResourceStructImp(resource_struct *master, ScopeImp *p) :
		StructImp(master, p, StructImp::Resource) { }

resource_struct::~resource_struct() {
	// TODO Auto-generated destructor stub
}

ResourceStructImp::~ResourceStructImp() {
	// TODO Auto-generated destructor stub
}


} /* namespace pss */
