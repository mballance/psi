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

#include "../../include/prv/expr.h"
#include "classlib/base_item.h"
#include "classlib/expr_list.h"
#include "classlib/expr_list_builder.h"

namespace pss {

class BaseItemImp {
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

	BaseItemImp();

//	BaseItemImp(const base_item &rhs);

	uint32_t depth() const { return m_depth; }

	virtual void setParent(base_item *p);
	virtual void setParent(BaseItemImp *p);

	virtual BaseItemImp *getParent() const {
		return m_parent;
	}

	inline ObjectType getObjectType() const {
		return m_type;
	}

	// Effectively private.
	virtual void add(BaseItemImp *item, bool reparent=true);

	virtual void remove(BaseItemImp *item);

	void setObjectType(ObjectType t);

	virtual const std::vector<BaseItemImp *> &getChildren() const;

	static const char *toString(ObjectType t);

	virtual ~BaseItemImp();

	static BaseItemImp *toImp(base_item *i);

	base_item *master() const { return m_master; }

	void setMaster(base_item *m) { m_master = m; }

	void inc_refcnt();

	void dec_refcnt();

	void operator = (const BaseItemImp &rhs);

	static base_item *pOrGlobal(base_item *p);

protected:

	BaseItemImp(base_item *master, ObjectType t, base_item *p);


private:
	uint32_t								m_refcnt;
	base_item								*m_master;
	ObjectType								m_type;
	BaseItemImp								*m_parent;
	uint32_t								m_depth;

	std::vector<BaseItemImp *>				m_children;
};


} /* namespace pss */

#endif /* TYPE_H_ */
