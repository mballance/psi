/*
 * BaseItem.cpp
 *
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
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#include "classlib/BaseItem.h"
#include "BaseItemImp.h"
#include "NamedBaseItemImp.h"

#include <stdio.h>

#include "ExprImp.h"

namespace psi {

BaseItem::BaseItem(BaseItemImp *impl) {
	m_impl = impl;
}

BaseItemImp::BaseItemImp(BaseItem *master, ObjectType t, BaseItemImp *p) :
		m_master(master), m_type(t), m_parent(p) {

	if (p) {
		p->add(this);
	}
}

BaseItem::~BaseItem() {
	delete m_impl;
}

BaseItemImp::~BaseItemImp() {
	// TODO Auto-generated destructor stub
}

BaseItemImp *BaseItemImp::toImp(BaseItem *i) {
	return (i)?i->impl():0;
}

Expr BaseItem::operator [] (const Expr &rhs) {
	return Expr(ExprImp(0, new ExprCore(ExprImp::BinOp_ArrayRef, *this, rhs)));
}

ExprListBuilder BaseItem::operator,(const BaseItem &rhs) {
	return ExprListBuilder(*this, rhs);
}

void BaseItemImp::add(BaseItemImp *item) {
//	NamedBaseItem *ni_t = NamedBaseItem::to(this);
//	NamedBaseItem *ni_it = NamedBaseItem::to(item);
//
//	fprintf(stdout, "add %d (%s) -> %d (%s)\n",
//			item->getObjectType(),
//			(ni_it)?ni_it->getName().c_str():"NULL",
//			getObjectType(),
//			(ni_t)?ni_t->getName().c_str():"NULL");
	m_children.push_back(item);
}

void BaseItemImp::setObjectType(ObjectType t) {
	m_type = t;
}

const std::vector<BaseItemImp *> &BaseItemImp::getChildren() const {
	return m_children;
}

const char *BaseItemImp::toString(ObjectType t) {
	switch (t) {
		case TypeAction: return "TypeAction";
		case TypeBind: return "TypeBind";
		case TypeBit: return "TypeBit";
		case TypeBool: return "TypeBool";
		case TypeChandle: return "TypeChandle";
		case TypeComponent: return "TypeComponent";
		case TypeConstraint: return "TypeConstraint";
		case TypeImport: return "TypeImport";
		case TypeInt: return "TypeInt";
		case TypeExec: return "TypeExec";
		case TypeExportItem: return "TypeExportItem";
		case TypeExtendAction: return "TypeExtendAction";
		case TypeExtendComponent: return "TypeExtendComponent";
		case TypeExtendStruct: return "TypeExtendStruct";
		case TypeField: return "TypeField";
		case TypeGraph: return "TypeGraph";
		case TypePackage: return "TypePackage";
		case TypeString: return "TypeString";
		case TypeStruct: return "TypeStruct";
		case Model: return "Model";
		case TypeRef: return "TypeRef";
	}

	return "Unknown";
}

} /* namespace psi */
