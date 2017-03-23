/*
 * state_struct.cpp
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
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#include "StateStructImp.h"

#include "../vendor/model_impl.h"
#include "NamedBaseItemImp.h"
#include "ScopeImp.h"

namespace pss {

state_struct::state_struct(const scope &p) :
		pss_struct(new StateStructImp(this, p.impl())), initial("initial") {
}

StateStructImp::StateStructImp(state_struct *master, ScopeImp *p) :
		StructImp(master, p, StructImp::State) {
	TypePathImp path = ModelImp::global()->getActiveTypeName(master);
	setName(path.leaf());

	// TODO: mark 'initial' as an internal field
//	initial.setInternal(true);
}

state_struct::~state_struct() {
	// TODO Auto-generated destructor stub
}

StateStructImp::~StateStructImp() {
	// TODO Auto-generated destructor stub
}

} /* namespace pss */
