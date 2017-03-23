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

#include "attr_item_impl.h"
#include "model_impl.h"
#include "scope.h"
#include "component.h"

namespace pss {

component::component(const scope &p) : vendor::component_impl(p) {

}

component::~component() {
	// TODO Auto-generated destructor stub
}

component::operator attr_item_impl &() const {
	return getField();
}

namespace vendor {

component_impl::component_impl(const scope &p) :
		named_base_item(
				base_item::TypeComponent,
				model_impl::global()->getParent(),
				p.name()), m_field(0) {

	bool is_field = model_impl::global()->isField();
	bool is_parent_field = model_impl::global()->isParentField();

	if (is_field) {
		// Create a field to represent this component and add it to the
		// parent context

		// First, remove ourselves from the children list
		getParent()->remove(this);

		// Any children of this component must be added to the field
		m_field = new attr_item_impl(
				getParent(),
				model_impl::global()->get_field_name(),
				attr_item_impl::AttrNone,
				model_impl::global()->getActiveType(this),
				0);
	}

	setName(model_impl::global()->getActiveTypeName(this).leaf());
	m_super_type = model_impl::global()->getSuperType();
}


component_impl::~component_impl() {
	// TODO Auto-generated destructor stub
}

const std::string &component_impl::getName() const {
	if (m_field) {
		return static_cast<attr_item_impl *>(m_field)->getName();
	} else {
		return named_base_item::getName();
	}
}


} /* namespace vendor */
} /* namespace pss */
