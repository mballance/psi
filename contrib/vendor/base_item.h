/*
 * base_item.h
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
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_BASE_ITEM_IMP_H
#define INCLUDED_BASE_ITEM_IMP_H
#include <string>
#include <vector>

//#include "classlib/expr.h"
//#include "classlib/expr_list.h"
//#include "classlib/expr_list_builder.h"

namespace pss {
namespace vendor {

class base_item {
public:

	enum ObjectType {
		TypeAction,    // 0
		TypeBind,
		TypeBit,
		TypeBool,
		TypeChandle,
		TypeComponent, // 5
		TypeConstraint,
		TypeImport,
		TypeInt,
		TypeExec, // exec
		TypeExportItem, // 10
		TypeExtendAction,
		TypeExtendComponent,
		TypeExtendStruct,
		TypeField, // 14
		TypeGraph, // 15
		TypePackage,
		TypeString,
		TypeStruct, // 18
		Model, // 19
		TypeRef
	};

public:

	base_item();

//	base_item(const base_item &rhs);

	uint32_t depth() const { return m_depth; }

	virtual void setParent(base_item *p);

	virtual base_item *getParent() const {
		return m_parent;
	}

	inline ObjectType getObjectType() const {
		return m_type;
	}

	// Effectively private.
	virtual void add(base_item *item, bool reparent=true);

	virtual void remove(base_item *item);

	void setObjectType(ObjectType t);

	virtual const std::vector<base_item *> &getChildren() const;

	static const char *toString(ObjectType t);

	virtual ~base_item();

	static base_item *toImp(base_item *i);

	static base_item *pOrGlobal(base_item *p);

protected:

	base_item(ObjectType t, base_item *p);


private:
	ObjectType								m_type;
	base_item								*m_parent;
	uint32_t								m_depth;

	std::vector<base_item *>				m_children;
};


} /* namespace vendor */
} /* namespace pss */

#endif /* TYPE_H_ */
