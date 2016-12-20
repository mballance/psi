/*
 * FieldItem.h
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
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_FIELD_ITEM_H
#define INCLUDED_FIELD_ITEM_H
#include <string>
#include "classlib/BaseItem.h"

namespace pss {

class MethodParamList;
class ExecStmt;
class ExecImportCallStmt;
class Scope;

class FieldItem: public BaseItem {
public:
	enum FieldAttr {
		AttrNone = 0,
		AttrInput,
		AttrOutput,
		AttrInout, // Only used for method parameters
		AttrLock,
		AttrShare,
		AttrRand,
		AttrPool
	};

public:
	virtual ~FieldItem();

	FieldItem(
			const Scope			&scope,
			FieldAttr			modifiers,
			const BaseItem		&type_hndl,
			const Expr			*array_dim);

	FieldItem(
			const Scope			&scope,
			FieldAttr			modifiers,
			const BaseItem		*type_hndl,
			const Expr			*array_dim);

	FieldItem(
			// Parent handle
			BaseItem 			*p,
			// Name of the field
			const std::string 	&name,
			// Array dimension
			const Expr			*array_dim,
			// Attribute of the field
			FieldAttr 			modifiers,
			// Handle to the instantiating object
			BaseItem			*wrapper,
			// Handle to the type object, if this is a user-defined type
			BaseItem			*type_hndl);

	Expr implies(const ExprList &rhs);

	MethodParamList operator,(const FieldItem &rhs);

	ExecStmt operator =(const ExecImportCallStmt &rhs);

	ExecStmt operator =(const Expr &rhs);

	ExecStmt operator +=(const ExecImportCallStmt &rhs);

	ExecStmt operator +=(const Expr &rhs);

	ExecStmt operator -=(const ExecImportCallStmt &rhs);

	ExecStmt operator -=(const Expr &rhs);

	ExecStmt operator <<=(const ExecImportCallStmt &rhs);

	ExecStmt operator <<=(const Expr &rhs);

	ExecStmt operator >>=(const ExecImportCallStmt &rhs);

	ExecStmt operator >>=(const Expr &rhs);

	ExecStmt operator |=(const ExecImportCallStmt &rhs);

	ExecStmt operator |=(const Expr &rhs);

	ExecStmt operator &= (const ExecImportCallStmt &rhs);

	ExecStmt operator &= (const Expr &rhs);

};

} /* namespace pss */

#endif /* INCLUDED_FIELD_ITEM_H */
