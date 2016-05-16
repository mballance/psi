/*
 * Type.h
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

namespace psi {

class Action;
class Struct;

class Type {
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
		TypeRegistry,
		TypeRef
	};

	public:

		virtual Type *getParent() const {
			return m_parent;
		}

		inline Type::ObjectType getObjectType() const {
			return m_type;
		}

		inline const std::string &getName() const { return m_name; }

		inline bool isRand() const { return m_isRand; }

		inline void setIsRand(bool r) { m_isRand = r; }

		inline bool isInput() const { return m_isInput; }

		inline void setIsInput(bool i) { m_isInput = i; m_isOutput = false; }

		inline bool isOutput() const { return m_isOutput; }

		inline void setIsOutput(bool o) { m_isOutput = o; m_isInput = false; }

		inline Type *getTypeData() const { return m_type_data; }

		inline void setTypeData(Type *t) { m_type_data = t; }

		inline const std::string &getTypeName() const { return m_type_name; }

		inline void setTypeName(const std::string &name) { m_type_name = name; }

		Type *operator ()()  { return this; }

		Expr operator [] (const Expr &rhs);

		ExprList operator,(Type &rhs);

		Expr operator = (const Expr &rhs);

//		Expr operator = (const ExprImportCall &rhs);

		// Effectively private.
		virtual void add(Type *item);

		void setObjectType(Type::ObjectType t);

		virtual const std::vector<Type *> &getChildren() const;

		static const char *toString(ObjectType t);

	protected:

		Type(Type::ObjectType t, Type *p);

		Type(Type::ObjectType t, Type *p, const std::string &name);

		virtual ~Type();


	private:

		bool insideInstance();

	private:
		ObjectType					m_type;
		std::string					m_name;
		Type						*m_parent;

		std::vector<Type *>			m_children;

		// Handle to the declaring type for fields
		Type						*m_type_data;
		// Name of the declaring type
		std::string					m_type_name;

		// Mutually-exclusive (?)
		bool						m_isRand;
		bool						m_isInput;
		bool						m_isOutput;

};

class TypeRef : public Type {
public:
	TypeRef(const std::string &str) : Type(Type::TypeAction, 0) { }
};

} /* namespace psi */

#endif /* TYPE_H_ */
