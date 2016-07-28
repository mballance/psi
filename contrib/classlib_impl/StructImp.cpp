/*
 * Struct.cpp
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

#include "StructImp.h"

namespace psi {

Struct::Struct(const Scope &p) :
	BaseItem(new StructImp(this, p.impl())) { }

//				m_structType(Struct::Base) {
//	m_super_type = Model::global()->getSuperType(this);
//	setName(Model::global()->getActiveTypeName(this).leaf());
//	m_ctxt = 0;
//	m_hndl = 0;
//}

StructImp::StructImp(
		Struct		*master,
		ScopeImpl	*p,
		StructType	t) :
	NamedBaseItemImp(master, BaseItemImp::TypeStruct, p->parent(), ""),
	m_struct_type(t) {
	m_super_type = ModelImpl::global()->getSuperType(this);
	setName(ModelImpl::global()->getActiveTypeName(this).leaf());
}

Struct::~Struct() {
	// TODO Auto-generated destructor stub
}

StructImp::~StructImp() {
	// TODO Auto-generated destructor stub
}

void Struct::pre_solve() {

}

void Struct::post_solve() {

}

void Struct::body() {

}

//void Struct::inline_exec_pre(IObjectContext *ctxt, psshandle_t *hndl) {
//	m_ctxt = ctxt;
//	m_hndl = hndl;
//}
//
//void Struct::inline_exec_post() {
//	m_ctxt = 0;
//	m_hndl = 0;
//
//}

} /* namespace psi */
