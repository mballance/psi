/*
 * Action.cpp
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
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "classlib/Action.h"

#include <stdio.h>
#include "classlib/Model.h"

namespace psi {

Action::Action(const Scope	&p) : NamedBaseItem(BaseItem::TypeAction, p.parent()) {
	m_super_type = Model::global()->getSuperType(this);
	m_ctxt = 0;
	m_hndl = 0;

	// TODO: need to deal with named scopes
	TypePath type = Model::global()->getActiveTypeName(this);
	setName(type.leaf());

//	const std::vector<const Scope *> &scope = Model::global()->get_scope();
//	fprintf(stdout, "--> scope %s\n", name.c_str());
//	for (int i=scope.size()-2; i>=0; i--) {
//		if (scope.at(i)->ctxt() != this) {
//			break;
//		}
//		fprintf(stdout, "  extends from %s\n", scope.at(i)->name());
//	}
//	fprintf(stdout, "<-- scope %s\n", name.c_str());
}

Action::~Action() {
	// TODO Auto-generated destructor stub
}

void Action::pre_solve() {

}

void Action::post_solve() {

}

void Action::body() {

}

void Action::inline_exec_pre(IObjectContext *ctxt, psshandle_t *hndl) {
	m_ctxt = ctxt;
	m_hndl = hndl;
}

void Action::inline_exec_post() {
	m_ctxt = 0;
	m_hndl = 0;
}

} /* namespace psi */
