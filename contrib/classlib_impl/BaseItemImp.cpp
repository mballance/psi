/*
 * base_item.cpp
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

#include "classlib/base_item.h"
#include "BaseItemImp.h"
#include "NamedBaseItemImp.h"
#include "ExprCore.h"
#include "ModelImp.h"

#include <stdio.h>

#include "ExprListBuilderImp.h"

namespace pss {

base_item::base_item(BaseItemImp *impl) : m_impl(impl) {
	m_impl->inc_refcnt();
	m_impl->setMaster(this);
}

base_item::base_item(const base_item &rhs) {
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

BaseItemImp::BaseItemImp(base_item *master, ObjectType t, base_item *p) :
		m_refcnt(0), m_master(master), m_type(t), m_parent(toImp(p)) {

	if (m_parent) {
		m_parent->add(this);
		m_depth = ModelImp::global()->depth();
	}
}

base_item::~base_item() {
	m_impl->dec_refcnt();
}

BaseItemImp::~BaseItemImp() {
	// TODO Auto-generated destructor stub
}

BaseItemImp *base_item::impl() const {
	return m_impl;
}

BaseItemImp *BaseItemImp::toImp(base_item *i) {
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

//void base_item::setParent(base_item *p) {
//	static_cast<BaseItemImp *>(impl())->setParent(p);
//}
//
void BaseItemImp::setParent(base_item *p) {
	m_parent = toImp(p);
}

void BaseItemImp::setParent(BaseItemImp *p) {
	m_parent = p;
}

base_item *BaseItemImp::pOrGlobal(base_item *p) {
	return (p)?p:ModelImp::global()->master();
}

expr base_item::operator [] (const expr &rhs) {
	return expr(ExprImp(new ExprCore(ExprImp::BinOp_ArrayRef, *this, rhs)));
}

expr_list_builder base_item::operator,(const base_item &rhs) {
	return expr_list_builder(*this, rhs);
}

void BaseItemImp::add(BaseItemImp *item, bool reparent) {
	if (reparent) {
		item->setParent(this);
	}
	m_children.push_back(item);
}

void BaseItemImp::remove(BaseItemImp *item) {
	std::vector<BaseItemImp *>::iterator it=m_children.end();

	if (m_children.size() > 0) {
		it--;
		while (true) {
			if (*it == item) {
				m_children.erase(it);
				break;
			} else if (it == m_children.begin()) {
				break;
			}
			it--;
		}
	}
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
