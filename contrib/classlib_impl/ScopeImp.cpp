/*
 * Scope.cpp
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
 *  Created on: Jul 7, 2016
 *      Author: ballance
 */

#include "ModelImp.h"
#include "ScopeImp.h"
#include <stdio.h>

namespace pss {

Scope::Scope(bool in_field_decl) {
	m_impl = new ScopeImp(this, &typeid(this), 0, in_field_decl, "");
}

ScopeImp::ScopeImp(
		Scope					*master,
		const std::type_info	*type,
		BaseItem				*ctxt,
		bool					in_field_decl,
		const std::string		&name) :
	m_master(master), m_type(type), m_ctxt(ctxt),
	m_in_field_decl(in_field_decl), m_name(name) {

	enter();

}

Scope::Scope(const char *name) {
	m_impl = new ScopeImp(this, 0, 0, true, name);
}

Scope::Scope(const std::string &name) {
	m_impl = new ScopeImp(this, 0, 0, true, name);
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

	if (m_in_field_decl) {
		return 0;
	} else {
		const std::vector<const ScopeImp *> &scope = ModelImp::global()->get_scope();
		BaseItem *ret = ModelImp::global()->master();

		// Return the first case where m_parent != this
//		fprintf(stdout, "--> parent() ctxt=%p type=%s\n", m_ctxt,
//				(m_type)?m_type->name():"unnamed");
		for (int i=scope.size()-1; i>=0; i--) {
//			fprintf(stdout, "  scope[%d] ctxt=%p in_field=%s\n",
//					i, scope.at(i)->m_ctxt, (scope.at(i)->m_in_field_decl)?"true":"false");
			if (scope.at(i)->m_in_field_decl) {
				ret = 0;
				break;
			} else if (scope.at(i)->m_ctxt && scope.at(i)->m_ctxt != m_ctxt) {
				ret = scope.at(i)->m_ctxt;
				break;
			}
		}
//		fprintf(stdout, "<-- parent() ctxt=%p ret=%p\n", m_ctxt, ret);

		return ret;
	}
}

const char *ScopeImp::name() const {
	return m_type->name();
}

void Scope::init(const std::type_info *type, BaseItem *ctxt) {
	m_impl = new ScopeImp(this, type, ctxt, false, "");
}

void ScopeImp::enter() {
	ModelImp::global()->push_scope(this);
}

void ScopeImp::leave() {
	ModelImp::global()->pop_scope(this);
}

} /* namespace pss */
