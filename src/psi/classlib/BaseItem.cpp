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

#include <stdio.h>
#include "classlib/ExprCore.h"

namespace psi {

BaseItem::BaseItem(BaseItem::ObjectType t, BaseItem *p) :
		m_type(t), m_name(""), m_parent(p),
		m_type_data(0), m_attr(AttrNone) {
	if (p) {
		p->add(this);
	}
}

BaseItem::BaseItem(BaseItem::ObjectType t, BaseItem *p, const std::string &name) :
		m_type(t), m_name(name), m_parent(p),
		m_type_data(0), m_attr(AttrNone) {

	if (p) {
		fprintf(stdout, "%s: Adding to scope\n", m_name.c_str());
		p->add(this);
	} else {
		fprintf(stdout, "%s: Scope is NULL\n", m_name.c_str());
	}
}

BaseItem::~BaseItem() {
	// TODO Auto-generated destructor stub
}

Expr BaseItem::operator [] (const Expr &rhs) {
	return Expr(new ExprCore(Expr::BinOp_ArrayRef, *this, rhs));
}

ExprListBuilder BaseItem::operator,(const BaseItem &rhs) {
	return ExprListBuilder(*this, rhs);
}

void BaseItem::add(BaseItem *item) {
	m_children.push_back(item);
}

void BaseItem::setObjectType(BaseItem::ObjectType t) {
	m_type = t;
}

const std::vector<BaseItem *> &BaseItem::getChildren() const {
	return m_children;
}

const char *BaseItem::toString(ObjectType t) {
	switch (t) {
		case TypeAction: return "TypeAction";
		case TypeBit: return "TypeBit";
		case TypeBool: return "TypeBool";
		case TypeChandle: return "TypeChandle";
		case TypeComponent: return "TypeComponent";
		case TypeConstraint: return "TypeConstraint";
		case TypeImport: return "TypeImport";
		case TypeInt: return "TypeInt";
		case TypeExec: return "TypeExec";
		case TypeExtendAction: return "TypeExtendAction";
		case TypeExtendComponent: return "TypeExtendComponent";
		case TypeExtendStruct: return "TypeExtendStruct";
		case TypePackage: return "TypePackage";
		case TypeString: return "TypeString";
		case TypeStruct: return "TypeStruct";
		case Model: return "Model";
		case TypeRef: return "TypeRef";
	}

	return "Unknown";
}

bool BaseItem::insideInstance() {
	bool ret = false;

	return ret;
}


} /* namespace psi */
