/*
 * ActionImp.cpp
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

#include <stdio.h>

#include "classlib/action.h"
#include "ActionImp.h"
#include "ModelImp.h"

namespace pss {

action::action(const Scope	&p) :
			BaseItem(new ActionImp(this, p.impl())) { }

ActionImp::ActionImp(action *master, ScopeImp *p) :
		NamedBaseItemImp(master, BaseItemImp::TypeAction, p->parent()) {
	m_super_type = ModelImp::global()->getSuperType(master);
	m_model = 0;
	m_hndl = 0;

	// TODO: need to deal with named scopes
	TypePathImp type = ModelImp::global()->getActiveTypeName(master);
	setName(type.leaf());
}

action::~action() {
}

ActionImp::~ActionImp() {
}

void action::pre_solve() {

}

void action::post_solve() {

}

void action::body() {

}

void ActionImp::pre_solve() {
	static_cast<action *>(master())->pre_solve();
}

void ActionImp::post_solve() {
	static_cast<action *>(master())->post_solve();
}

void ActionImp::body() {
	static_cast<action *>(master())->body();
}

void ActionImp::inline_exec_pre(IModel *model, psshandle_t hndl) {
	m_model = model;
	m_hndl = hndl;
}

void ActionImp::inline_exec_post() {
	m_model = 0;
	m_hndl = 0;
}

} /* namespace pss */
