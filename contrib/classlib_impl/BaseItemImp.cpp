/*
 * BaseItem.cpp
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

#include "classlib/BaseItem.h"
#include "BaseItemImp.h"
#include "NamedBaseItemImp.h"
#include "ExprCore.h"
#include "ModelImp.h"

#include <stdio.h>

#include "ExprListBuilderImp.h"

namespace pss {

BaseItem::BaseItem(BaseItemImp *impl) : m_impl(impl) {
	m_impl->inc_refcnt();
	m_impl->setMaster(this);
}

BaseItem::BaseItem(const BaseItem &rhs) {
	m_impl = rhs.m_impl;
	m_impl->inc_refcnt();
}

BaseItemImp::BaseItemImp() :
		m_refcnt(0),
		m_master(0),
		m_type(Model),
		m_parent(0) {
	m_depth = 0;
}

// Is this constructor required?
//BaseItemImp::BaseItemImp(const BaseItem &rhs) {
//	m_master = 0;
//	m_type = rhs.impl()->m_type;
//	m_parent = rhs.impl()->m_parent;
//	m_children = rhs.impl()->m_children;
//	m_depth = rhs.impl()->m_depth;
//}

BaseItemImp::BaseItemImp(BaseItem *master, ObjectType t, BaseItem *p) :
		m_refcnt(0), m_master(master), m_type(t), m_parent(toImp(p)) {

	if (m_parent) {
		m_parent->add(this);
		m_depth = ModelImp::global()->depth();
	}
}

BaseItem::~BaseItem() {
	m_impl->dec_refcnt();
}

BaseItemImp::~BaseItemImp() {
	// TODO Auto-generated destructor stub
}

BaseItemImp *BaseItem::impl() const {
	return m_impl;
}

BaseItemImp *BaseItemImp::toImp(BaseItem *i) {
	return (i)?i->impl():0;
}

void BaseItemImp::inc_refcnt() {
	m_refcnt++;
}

void BaseItemImp::dec_refcnt() {
	if (!m_refcnt) {
		// Error: too many frees
	}
	m_refcnt--;

	if (!m_refcnt) {
		delete this;
	}
}

//void BaseItem::setParent(BaseItem *p) {
//	static_cast<BaseItemImp *>(impl())->setParent(p);
//}
//
void BaseItemImp::setParent(BaseItem *p) {
	m_parent = toImp(p);
}

void BaseItemImp::setParent(BaseItemImp *p) {
	m_parent = p;
}

BaseItem *BaseItemImp::pOrGlobal(BaseItem *p) {
	return (p)?p:ModelImp::global()->master();
}

Expr BaseItem::operator [] (const Expr &rhs) {
	return Expr(ExprImp(new ExprCore(ExprImp::BinOp_ArrayRef, *this, rhs)));
}

ExprListBuilder BaseItem::operator,(const BaseItem &rhs) {
	return ExprListBuilder(*this, rhs);
}

void BaseItemImp::add(BaseItemImp *item, bool reparent) {
	if (reparent) {
		item->setParent(this);
	}
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

} /* namespace pss */
