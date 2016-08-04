/*
 * StateStruct.cpp
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
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#include "StateStructImp.h"

#include "NamedBaseItemImp.h"
#include "ModelImp.h"
#include "ScopeImp.h"

namespace pss {

StateStruct::StateStruct(const Scope &p) :
		Struct(new StateStructImp(this, p.impl())), initial(this, "initial") {
}

StateStructImp::StateStructImp(StateStruct *master, ScopeImp *p) :
		StructImp(master, p, StructImp::State) {
	TypePathImp path = ModelImp::global()->getActiveTypeName(master);
	setName(path.leaf());

	// TODO: mark 'initial' as an internal field
//	initial.setInternal(true);
}

StateStruct::~StateStruct() {
	// TODO Auto-generated destructor stub
}

StateStructImp::~StateStructImp() {
	// TODO Auto-generated destructor stub
}

} /* namespace pss */
