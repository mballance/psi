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
#include "ComponentImp.h"

namespace pss {

action::action(const Scope	&p) :
			BaseItem(new ActionImp(this, p.impl())) { }

ActionImp::ActionImp(action *master, ScopeImp *p) :
		NamedBaseItemImp(master, BaseItemImp::TypeAction, p->parent()),
		m_field(0), m_model(0), m_hndl(0) {

	bool is_field = ModelImp::global()->isField();
	bool is_parent_field = ModelImp::global()->isParentField();

	if (is_field) {
		m_super_type = ModelImp::global()->getSuperType(master);
	} else {
		m_super_type = TypePathImp();
	}

	// TODO: need to deal with named scopes
	TypePathImp type = ModelImp::global()->getActiveTypeName(master);
	setName(type.leaf());

	fprintf(stdout, "ActionImp::ActionImp is_field=%s name=%s\n",
			is_field?"true":"false",
			getName().c_str());

	if (is_field) {
		const char *field_name = ModelImp::global()->get_field_name(master);

		// First, remove ourselves
		getParent()->remove(this);

		m_field = new FieldItemImp(
				0, // master
				getParent()->master(),
				field_name,
				0,
				FieldItem::AttrNone,
				0, // wrapper
				ModelImp::global()->getActiveType(master));
	}
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

const std::string &ActionImp::getName() const {
	if (m_field) {
		return m_field->getName();
	} else {
		return NamedBaseItemImp::getName();
	}
}

} /* namespace pss */
