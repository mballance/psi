/*
 * Struct.cpp
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

namespace pss {

Struct::Struct(const Scope &p) :
	BaseItem(new StructImp(this, p.impl())) { }

Struct::Struct(BaseItemImp *imp) : BaseItem(imp) { }

StructImp::StructImp(
		Struct		*master,
		ScopeImp	*p,
		StructType	t) :
	NamedBaseItemImp(master, BaseItemImp::TypeStruct, p->parent(), ""),
	m_struct_type(t) {
	m_super_type = ModelImp::global()->getSuperType(master);
	setName(ModelImp::global()->getActiveTypeName(master).leaf());
	m_model = 0;
	m_hndl = 0;
}

Struct::~Struct() {
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

void Struct::pre_solve() {

}

void Struct::post_solve() {

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

} /* namespace pss */
