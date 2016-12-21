/*
 * Scope.cpp
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

//Scope::Scope(bool is_field) {
//	m_impl = new ScopeImp(this, &typeid(this), 0, is_field, "", 0);
//}

ScopeImp::ScopeImp(
		Scope					*master,
		const std::type_info	*type,
		BaseItem				*ctxt,
		bool					is_field,
		const std::string		&name,
		BaseItem				*type_id) :
	m_master(master), m_type(type), m_ctxt(ctxt),
	m_is_field(is_field), m_name(name),
	m_type_id(type_id) {

	enter();

}

ScopeImp::ScopeImp(BaseItem *ctxt) {
	m_master = 0;
	m_type = 0;
	m_is_field = false;
	m_type_id = 0;
	m_ctxt = ctxt;
}

Scope::Scope(const char *name) {
	m_impl = new ScopeImp(this, 0, 0,
			(name!=0), (name)?name:"", 0);
}

Scope::Scope(const std::string &name) {
	m_impl = new ScopeImp(this, 0, 0, true, name, 0);
}

Scope::~Scope() {
	delete m_impl;
}

ScopeImp::~ScopeImp() {
	leave();
}

ScopeImp *Scope::impl() const {
	return m_impl;
}

BaseItem *ScopeImp::parent() const {
/*	if (m_is_field) {
		return 0;
	} else */{
		return ModelImp::global()->getParentScope();
//		const std::vector<const ScopeImp *> &scope = ModelImp::global()->get_scope();
//		BaseItem *ret = ModelImp::global()->master();
//
//		// Return the first case where m_parent != this
//		fprintf(stdout, "--> parent() ctxt=%p type=%s\n", m_ctxt,
//				(m_type)?m_type->name():"unnamed");
//		for (int i=scope.size()-1; i>=0; i--) {
//			fprintf(stdout, "  scope[%d] ctxt=%p in_field=%s\n",
//					i, scope.at(i)->m_ctxt, (scope.at(i)->m_is_field)?"true":"false");
//			if (scope.at(i)->m_is_field) {
//				ret = 0;
//				break;
//			} else if (scope.at(i)->m_ctxt && scope.at(i)->m_ctxt != m_ctxt) {
//				ret = scope.at(i)->m_ctxt;
//				break;
//			}
//		}
//
//		if (!ret) {
//
//		}
//
//		fprintf(stdout, "<-- parent() ctxt=%p ret=%p\n", m_ctxt, ret);
//
//		return ret;
	}
}

const char *ScopeImp::name() const {
	return m_type->name();
}

void Scope::init(const std::type_info *type, BaseItem *ctxt, BaseItem *type_id) {
	// TODO: type_id
	m_impl = new ScopeImp(this, type, ctxt, false, "", type_id);
}

void ScopeImp::enter() {
	ModelImp::global()->push_scope(this);
}

void ScopeImp::leave() {
	ModelImp::global()->pop_scope(this);
}

} /* namespace pss */
