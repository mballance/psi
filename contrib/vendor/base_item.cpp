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

#include "base_item.h"
//#include "NamedBaseItemImp.h"
//#include "ExprCore.h"
#include <stdio.h>

#include "model_impl.h"
//#include "ExprListBuilderImp.h"

namespace pss {
namespace vendor {

base_item::base_item() :
		m_type(Model),
		m_parent(0) {
	m_depth = 0;
}

base_item::base_item(ObjectType t, base_item *p) : m_type(t), m_parent(p) {

	if (m_parent) {
		m_parent->add(this);
		m_depth = model_impl::global()->depth();
	}
}

base_item::~base_item() {
	// TODO Auto-generated destructor stub
}

void base_item::setParent(base_item *p) {
	m_parent = p;
}

base_item *base_item::pOrGlobal(base_item *p) {
	return (p)?p:model_impl::global();
}

//expr base_item::operator [] (const expr &rhs) {
//	return expr(ExprImp(new ExprCore(ExprImp::BinOp_ArrayRef, *this, rhs)));
//}
//
//expr_list_builder base_item::operator,(const base_item &rhs) {
//	return expr_list_builder(*this, rhs);
//}

void base_item::add(base_item *item, bool reparent) {
	if (reparent) {
		item->setParent(this);
	}
	m_children.push_back(item);
}

void base_item::remove(base_item *item) {
	std::vector<base_item *>::iterator it=m_children.end();

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

void base_item::setObjectType(ObjectType t) {
	m_type = t;
}

const std::vector<base_item *> &base_item::getChildren() const {
	return m_children;
}

const char *base_item::toString(ObjectType t) {
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

} /* namespace vendor */
} /* namespace pss */
