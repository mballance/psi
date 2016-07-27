/*
 * BaseItem.h
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
 *
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_BASE_ITEM_IMPL_H
#define INCLUDED_BASE_ITEM_IMPL_H
#include <string>
#include <vector>

#include "classlib/BaseItem.h"
#include "classlib/Expr.h"
#include "classlib/ExprList.h"
#include "classlib/ExprListBuilder.h"

namespace psi {

class BaseItemImpl {
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
		TypeExec,
		TypeExportItem, // 10
		TypeExtendAction,
		TypeExtendComponent,
		TypeExtendStruct,
		TypeField,
		TypeGraph,
		TypePackage,
		TypeString,
		TypeStruct, // 18
		Model, // 19
		TypeRef
	};

public:

	virtual void setParent(BaseItemImpl *p) { m_parent = p; }

	virtual BaseItemImpl *getParent() const {
		return m_parent;
	}

	inline ObjectType getObjectType() const {
		return m_type;
	}

	// Effectively private.
	virtual void add(BaseItemImpl *item);

	void setObjectType(ObjectType t);

	virtual const std::vector<BaseItemImpl *> &getChildren() const;

	static const char *toString(ObjectType t);

	virtual ~BaseItemImpl();

protected:

	BaseItemImpl(BaseItem *master, ObjectType t, BaseItemImpl *p);

private:
	BaseItem					*m_master;
	ObjectType					m_type;
	BaseItemImpl				*m_parent;

	std::vector<BaseItemImpl *>	m_children;
};

} /* namespace psi */

#endif /* TYPE_H_ */
