/*
 * ActionImp.cpp
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

#include <stdio.h>

#include "classlib/Action.h"
#include "ActionImp.h"
#include "ModelImp.h"

namespace psi {

Action::Action(const Scope	&p) :
			BaseItem(new ActionImp(this, p.impl())) { }

ActionImp::ActionImp(Action *master, ScopeImp *p) :
		NamedBaseItemImp(master, BaseItemImp::TypeAction, p->parent()) {
	m_super_type = ModelImp::global()->getSuperType(master);
	m_ctxt = 0;
	m_hndl = 0;

	// TODO: need to deal with named scopes
	TypePathImp type = ModelImp::global()->getActiveTypeName(master);
	setName(type.leaf());
}

Action::~Action() {
}

ActionImp::~ActionImp() {
}

void Action::pre_solve() {

}

void Action::post_solve() {

}

void Action::body() {

}

void ActionImp::pre_solve() {

}

void ActionImp::post_solve() {

}

void ActionImp::body() {

}

void ActionImp::inline_exec_pre(IObjectContext *ctxt, psshandle_t *hndl) {
	m_ctxt = ctxt;
	m_hndl = hndl;
}

void ActionImp::inline_exec_post() {
	m_ctxt = 0;
	m_hndl = 0;
}

} /* namespace psi */
