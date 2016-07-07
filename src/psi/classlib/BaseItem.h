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

#ifndef TYPE_H_
#define TYPE_H_
#include <string>
#include <vector>

#include "classlib/Expr.h"
#include "classlib/ExprList.h"
#include "classlib/ExprListBuilder.h"

namespace psi {

class Action;
class Struct;

class BaseItem {
	friend class Struct;

public:
	enum ObjectType {
		TypeAction,
		TypeBind,
		TypeBit,
		TypeBool,
		TypeChandle,
		TypeComponent,
		TypeConstraint,
		TypeImport,
		TypeInt,
		TypeExec,
		TypeExportAction,
		TypeExtendAction,
		TypeExtendComponent,
		TypeExtendStruct,
		TypeGraph,
		TypePackage,
		TypeString,
		TypeStruct,
		Model,
		TypeRef
	};

	enum FieldAttr {
		AttrNone = 0,
		AttrInput,
		AttrOutput,
		AttrLock,
		AttrShare,
		AttrRand,
		AttrPool
	};

	public:

		virtual BaseItem *getParent() const {
			return m_parent;
		}

		inline BaseItem::ObjectType getObjectType() const {
			return m_type;
		}

		inline const std::string &getName() const { return m_name; }

		FieldAttr getAttr() const { return m_attr; }

		void setAttr(FieldAttr attr) { m_attr = attr; }

		inline void setTypeData(BaseItem *t) { m_type_data = t; }

		inline BaseItem *getTypeData() const { return m_type_data; }

		BaseItem *operator ()()  { return this; }

		Expr operator [] (const Expr &rhs);

		ExprListBuilder operator,(const BaseItem &rhs);

		Expr operator = (const Expr &rhs);

//		Expr operator = (const ExprImportCall &rhs);

		// Effectively private.
		virtual void add(BaseItem *item);

		void setObjectType(BaseItem::ObjectType t);

		virtual const std::vector<BaseItem *> &getChildren() const;

		static const char *toString(ObjectType t);

	protected:

		BaseItem(BaseItem::ObjectType t, BaseItem *p);

		BaseItem(BaseItem::ObjectType t, BaseItem *p, const std::string &name);

		virtual ~BaseItem();


	private:

		bool insideInstance();

	private:
		ObjectType					m_type;
		std::string					m_name;
		BaseItem						*m_parent;


		std::vector<BaseItem *>			m_children;

		// Handle to the declaring type for fields
		BaseItem						*m_type_data;

		FieldAttr					m_attr;

};

class TypeRef : public BaseItem {
public:
	TypeRef(const std::string &str) : BaseItem(BaseItem::TypeAction, 0) { }
};

} /* namespace psi */

#endif /* TYPE_H_ */
