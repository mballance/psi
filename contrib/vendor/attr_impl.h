/*
 * attr_impl.h
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
#include "attr_item_impl.h"
#include "classlib/method_param_list.h"
#include "sav/type_decl.h"

namespace pss {
namespace vendor {

class method_param_list;
template <class T> class attr_impl : public T {
public:

	virtual ~attr_impl() { }

	/*
	 * Provide an explicit conversion function to tell the
	 * compiler how to interpret the fact that both we and T extend
	 * from base_item
	operator expr() const { return expr(m_field); }

	operator const attr_item &() const { return m_field; }
	 */

	// Helper operator used to form parameter lists
	method_param_list operator,(const attr_item &rhs) { return (m_field , rhs); }

public:
	// TODO: make type_decl<> a friend?
	attr_impl(const scope &scope) : T(static_cast<T *>(this)),
				m_field(this, attr_item::AttrNone,
						(type_decl<T>::valid())?type_decl<T>::id():0, 0) { }

protected:

	attr_impl(
			attr_item::FieldAttr 	attr,
			const scope				&scope) : T(static_cast<T *>(this)),
				m_field(this, attr,
						(type_decl<T>::valid())?type_decl<T>::id():0, 0) { }

	attr_impl(
			attr_item::FieldAttr 	attr,
			base_item 				*p,
			const std::string 		&name,
			const expr				&array_dim) : T(scope(true)),
				m_field(p, name, &array_dim, attr, this,
						(type_decl<T>::valid())?type_decl<T>::id():0) {
	}

protected:
	attr_item						m_field;

};

} /* namespace vendor */
}

#endif /* INCLUDED_FIELD_BASE_H */

