/*
 * pss_struct.cpp
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

#include "StructImp.h"
#include "ModelImp.h"
#include "ScopeImp.h"
#include "classlib/expr.h"

namespace pss {

pss_struct::pss_struct(const scope &p) :
	base_item(new StructImp(this, p.impl())) { }

pss_struct::pss_struct(BaseItemImp *imp) : base_item(imp) { }

StructImp::StructImp(
		pss_struct	*master,
		ScopeImp	*p,
		StructType	t) :
	NamedBaseItemImp(master, BaseItemImp::TypeStruct, p->parent(), ""),
	m_struct_type(t), m_model(0), m_hndl(0), m_field(0) {

	bool is_field = ModelImp::global()->isField();
	bool is_parent_field = ModelImp::global()->isParentField();

	m_super_type = ModelImp::global()->getSuperType();
	setName(ModelImp::global()->getActiveTypeName(master).leaf());

	if (is_field) {
		// First, remove ourselves from the children list
		getParent()->remove(this);

		// Any children of this component must be added to the field
		m_field = new attr_item(
				getParent()->master(),
				ModelImp::global()->get_field_name(),
				attr_item::AttrNone,
				ModelImp::global()->getActiveType(master)->master(),
				0);
	}
}

pss_struct::~pss_struct() {
	// TODO Auto-generated destructor stub
}

StructImp::~StructImp() {
	// TODO Auto-generated destructor stub
}

const TypePathImp &StructImp::getSuperType() const {
	return m_super_type;
}

StructImp::StructType StructImp::getStructType() const {
	return m_struct_type;
}

pss_struct::operator expr() const {
//	return expr(*m_field);
}

pss_struct::operator attr_item &() const {
	return static_cast<StructImp *>(impl())->getField();
}

void pss_struct::pre_solve() {

}

void pss_struct::post_solve() {

}

void StructImp::inline_exec_pre(IModel *model, psshandle_t hndl) {
	m_model = model;
	m_hndl  = hndl;
}

void StructImp::pre_solve() {

}

void StructImp::post_solve() {

}

void StructImp::inline_exec_post() {
	m_model = 0;
	m_hndl = 0;
}

const std::string &StructImp::getName() const {
	if (m_field) {
		return static_cast<FieldItemImp *>(m_field->impl())->getName();
	} else {
		return NamedBaseItemImp::getName();
	}
}

} /* namespace pss */
