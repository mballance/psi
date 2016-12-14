/*
 * FieldBase.h
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
 */
#ifndef INCLUDED_FIELD_BASE_H
#define INCLUDED_FIELD_BASE_H
#include "classlib/FieldItem.h"
#include "classlib/MethodParamList.h"
#include "classlib/type_decl.h"

namespace pss {

class MethodParamList;
template <class T> class FieldBase : public T {
public:

	virtual ~FieldBase() { }

	/*
	 * Provide an explicit conversion function to tell the
	 * compiler how to interpret the fact that both we and T extend
	 * from BaseItem
	 */
	operator Expr() const { return Expr(m_field); }

	operator const FieldItem &() const { return m_field; }

	// Helper operator used to form parameter lists
	MethodParamList operator,(const FieldItem &rhs) { return (m_field , rhs); }

protected:

	FieldBase(
			FieldItem::FieldAttr 	attr,
			BaseItem 				*p,
			const std::string 		&name) : T(Scope(true)),
				m_field(p, name, 0, attr, this,
						(type_decl<T>::valid())?type_decl<T>::id():0) {
	}

	FieldBase(
			FieldItem::FieldAttr 	attr,
			BaseItem 				*p,
			const std::string 		&name,
			const Expr				&array_dim) : T(Scope(true)),
				m_field(p, name, &array_dim, attr, this,
						(type_decl<T>::valid())?type_decl<T>::id():0) {
	}

protected:
	FieldItem						m_field;

};

}

#endif /* INCLUDED_FIELD_BASE_H */

