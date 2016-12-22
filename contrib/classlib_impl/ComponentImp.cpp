/*
 * component.cpp
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
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#include "ComponentImp.h"
#include "ScopeImp.h"
#include "ModelImp.h"
#include "classlib/FieldItem.h"
#include "FieldItemImp.h"

namespace pss {

component::component(const Scope &p) : BaseItem(new ComponentImp(this, p.impl())) {

}

ComponentImp::ComponentImp(component *master, ScopeImp *p) :
		NamedBaseItemImp(master, BaseItemImp::TypeComponent, p->parent()),
		m_field(0) {

	bool is_field = ModelImp::global()->isField();
	bool is_parent_field = ModelImp::global()->isParentField();

	fprintf(stdout, "ComponentImp::ComponentImp isField=%s isParentField=%s\n",
			ModelImp::global()->isField()?"true":"false",
			ModelImp::global()->isParentField()?"true":"false");

	if (is_field) {
		// Create a field to represent this component and add it to the
		// parent context

		// First, remove ourselves from the children list
		getParent()->remove(this);

		// Any children of this component must be added to the field
		m_field = new FieldItem(
				getParent()->master(),
				ModelImp::global()->get_field_name(),
				FieldItem::AttrNone,
				ModelImp::global()->getActiveType(master)->master(),
				0);
	} else {
		// Type registration
		fprintf(stdout, "TODO: this is a component type registration\n");
		ModelImp::print_scopes();
	}

	setName(ModelImp::global()->getActiveTypeName(master).leaf());
	m_super_type = ModelImp::global()->getSuperType();
}

component::~component() {
	// TODO Auto-generated destructor stub
}

ComponentImp::~ComponentImp() {
	// TODO Auto-generated destructor stub
}

const std::string &ComponentImp::getName() const {
	if (m_field) {
		return static_cast<FieldItemImp *>(m_field->impl())->getName();
	} else {
		return NamedBaseItemImp::getName();
	}
}

component::operator FieldItem &() const {
	return static_cast<ComponentImp *>(impl())->getField();
}

} /* namespace pss */
