/*
 * scope.cpp
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
 *  Created on: Jul 7, 2016
 *      Author: ballance
 */

#include "ModelImp.h"
#include "ScopeImp.h"
#include <stdio.h>

namespace pss {

ScopeImp::ScopeImp(
		scope					*master,
		const std::type_info	*type,
		base_item				*ctxt,
		bool					is_field,
		bool					is_type,
		const std::string		&name,
		base_item				*type_id) :
	m_master(master), m_type(type), m_ctxt(ctxt),
	m_is_field(is_field), m_is_type(is_type),
	m_name(name), m_type_id(type_id) {

	enter();

}

ScopeImp::ScopeImp(base_item *ctxt) {
	m_master = 0;
	m_type = 0;
	m_is_field = false;
	m_is_type = false;
	m_type_id = 0;
	m_ctxt = ctxt;
}

scope::scope(const char *name) {
	m_impl = new ScopeImp(this, 0, 0,
			(name!=0), false, (name)?name:"", 0);
}

scope::scope(bool is_type) {
	m_impl = new ScopeImp(this, 0, 0,
			false, // is_field
			true, // is_type,
			"",
			0);
}

scope::scope(const std::string &name) {
	m_impl = new ScopeImp(this, 0, 0, true, false, name, 0);
}

scope::~scope() {
	delete m_impl;
}

ScopeImp::~ScopeImp() {
	leave();
}

ScopeImp *scope::impl() const {
	return m_impl;
}

base_item *ScopeImp::parent() const {
	return ModelImp::global()->getParentScope();
}

const char *ScopeImp::name() const {
	return m_type->name();
}

void ScopeImp::set_scope_name(const std::string &name) {
	m_name = name;
}

void scope::init(const std::type_info *type, base_item *ctxt, base_item *type_id) {
	// TODO: type_id
	m_impl = new ScopeImp(this, type, ctxt, false, false, "", type_id);
}

void ScopeImp::enter() {
	ModelImp::global()->push_scope(this);
}

void ScopeImp::leave() {
	ModelImp::global()->pop_scope(this);
}

} /* namespace pss */
