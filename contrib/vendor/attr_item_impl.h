/*
 * attr_item_impl.h
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
#include "named_base_item.h"

namespace pss {
class scope;
class expr; // TODO:
namespace vendor {

class method_param_list;
class exec_stmt;
class exec_import_call_stmt;

class attr_item_impl: public named_base_item {
public:
	template <typename T> friend class rand_attr;

	enum FieldAttr {
		AttrNone = 0,
		AttrInput,
		AttrOutput,
		AttrInout, // Only used for method parameters
		AttrLock,
		AttrShare,
		AttrRand,
		AttrPool,
		AttrAction // action_attr
	};

public:
	virtual ~attr_item_impl();

	attr_item_impl(
			base_item			*p,
			const std::string	&name,
			FieldAttr			modifiers,
			const base_item		*type_hndl,
			const expr			*array_dim);

protected:
	attr_item_impl(
			const scope			&scope,
			FieldAttr			modifiers,
			const base_item		&type_hndl,
			const expr			*array_dim);

	attr_item_impl(
			const scope			&scope,
			FieldAttr			modifiers,
			const base_item		*type_hndl,
			const expr			*array_dim);

	attr_item_impl(
			// Parent handle
			base_item 			*p,
			// Name of the field
			const std::string 	&name,
			// Array dimension
			const expr			*array_dim,
			// Attribute of the field
			FieldAttr 			modifiers,
			// Handle to the instantiating object
			base_item			*wrapper,
			// Handle to the type object, if this is a user-defined type
			base_item			*type_hndl);

	/**
	 * The get method returns the solve-time value of this
	 * data field. Calling this method is only valid
	 * on fields of this type, and only from within an
	 * inline-exec callback.
	 */
	uint64_t get_bit();

	/**
	 * The set method sets the value of this data field.
	 * Calling this method is only valid on fields
	 * of this type, and only from within an
	 * inline-exec callback.
	 */
	void set_bit(uint64_t v);

	/**
	 * The get method returns the solve-time value of this
	 * data field. Calling this method is only valid
	 * on fields of this type, and only from within an
	 * inline-exec callback.
	 */
	int64_t get_int();

	/**
	 * The set method sets the value of this data field.
	 * Calling this method is only valid on fields
	 * of this type, and only from within an
	 * inline-exec callback.
	 */
	void set_int(int64_t v);

	base_item *getDataType() const { return m_data_type; }

	attr_item_impl::FieldAttr getAttr() const { return m_attr; }

	void setAttr(attr_item_impl::FieldAttr attr) { m_attr = attr; }

	void setInternal(bool i) { m_internal = i; }

	bool isInternal() const { return m_internal; }

	bool hasArrayDim() const { return m_has_array_dim; }

#ifdef UNDEFINED
	const expr &arrayDim() const { return m_array_dim; }
#endif


public:
	void setModifiers(FieldAttr modifiers);

#ifdef UNDEFINED
	expr implies(const expr_list &rhs);

	method_param_list operator,(const attr_item_impl &rhs);

	exec_stmt operator =(const exec_import_call_stmt &rhs);

	exec_stmt operator =(const expr &rhs);

	exec_stmt operator +=(const exec_import_call_stmt &rhs);

	exec_stmt operator +=(const expr &rhs);

	exec_stmt operator -=(const exec_import_call_stmt &rhs);

	exec_stmt operator -=(const expr &rhs);

	exec_stmt operator <<=(const exec_import_call_stmt &rhs);

	exec_stmt operator <<=(const expr &rhs);

	exec_stmt operator >>=(const exec_import_call_stmt &rhs);

	exec_stmt operator >>=(const expr &rhs);

	exec_stmt operator |=(const exec_import_call_stmt &rhs);

	exec_stmt operator |=(const expr &rhs);

	exec_stmt operator &= (const exec_import_call_stmt &rhs);

	exec_stmt operator &= (const expr &rhs);
#endif

private:
	base_item					*m_data_type;
	attr_item_impl::FieldAttr	m_attr;
	bool						m_internal;

	bool						m_has_array_dim;
	expr						*m_array_dim;
//	InlineExecUtil				m_utils;

};

} /* namespace vendor */
} /* namespace pss */

#endif /* INCLUDED_FIELD_ITEM_H */
