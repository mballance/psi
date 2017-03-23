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

#include "../vendor/model_impl.h"
#include "ComponentImp.h"
#include "With.h"

namespace pss {

action::action(const scope	&p) :
			base_item(new ActionImp(this, p.impl())) { }

ActionImp::ActionImp(action *master, ScopeImp *p) :
		NamedBaseItemImp(master, BaseItemImp::TypeAction, p->parent()),
		m_field(0), m_model(0), m_hndl(0) {

	bool is_type  = ModelImp::global()->isType();
	bool is_field = ModelImp::global()->isField();
	bool is_parent_field = ModelImp::global()->isParentField();

	if (is_type) {
		m_super_type = ModelImp::global()->getSuperType();
	} else {
		m_super_type = TypePathImp();
	}

	// TODO: need to deal with named scopes
	TypePathImp type = ModelImp::global()->getActiveTypeName(master);
	setName(type.leaf());

	if (is_field) {
		// First, remove ourselves
		getParent()->remove(this);

		m_field = new attr_item(
				getParent()->master(),
				ModelImp::global()->get_field_name(),
				attr_item::AttrNone,
				ModelImp::global()->getActiveType(master)->master(),
				0);
	} else {
		// This is a type reference
		m_field = new attr_item(
				0, // don't add this field in anywhere
				type.leaf(),
				attr_item::AttrNone,
				master, // We are the type
				0);
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

expr action::with(const expr_list &l) const {
	return With(*(static_cast<ActionImp *>(impl())->getField()), l);
}

action::operator attr_item &() const {
	return *(static_cast<ActionImp *>(impl())->getField());
}

expr action::mk_with(const expr_list &l) const {
	return With(*(static_cast<ActionImp *>(impl())->getField()), l);
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
		return static_cast<FieldItemImp *>(m_field->impl())->getName();
	} else {
		return NamedBaseItemImp::getName();
	}
}

} /* namespace pss */
