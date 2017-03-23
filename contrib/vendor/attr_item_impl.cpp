/*
 * attr_item_impl.cpp
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
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#include "attr_item_impl.h"

#include "../../include/prv/expr.h"
#include "model_impl.h"
#include "classlib/scope.h"
#include "BaseItemImp.h"
#include "ExecAssignCallStmtImp.h"
#include "ExecAssignExprStmtImp.h"
#include "ExecAssignStmtImp.h"
#include "ScopeImp.h"

namespace pss {
namespace vendor {

attr_item_impl::attr_item_impl(
		base_item				*p,
		const std::string		&name,
		FieldAttr				modifiers,
		const base_item			*type_hndl,
		const expr				*array_dim) : named_base_item(base_item::TypeField, p, name),
				m_data_type(0), m_attr(modifiers), m_internal(false),
				m_has_array_dim(array_dim != 0),
				m_array_dim(array_dim), m_utils(this) {

}

attr_item_impl::attr_item_impl(
		const scope					&p,
		attr_item_impl::FieldAttr 	modifiers,
		const base_item				&type_hndl,
		const expr					*array_dim) : named_base_item(base_item::TypeField,
				model_impl::global()->getParentScope(),
				model_impl::global()->get_field_name()),
				m_data_type(&type_hndl), // TODO:
				m_attr(modifiers),
				m_internal(false),
				m_has_array_dim(array_dim != 0),
				m_array_dim(array_dim) {
}

attr_item_impl::attr_item_impl(
		const scope				&p,
		attr_item_impl::FieldAttr 	modifiers,
		const base_item			*type_hndl,
		const expr				*array_dim) : named_base_item(base_item::TypeField,
				model_impl::global()->getParentScope(),
				model_impl::global()->get_field_name()),
				m_data_type(type_hndl),
				m_attr(modifiers),
				m_internal(false),
				m_has_array_dim(array_dim != 0),
				m_array_dim(array_dim) {
	// TODO: re-home the field if 'wrapper' is provided?
	// if (wrapper) {
	//   wrapper->setParent(p);
	// }
}

attr_item_impl::~attr_item_impl() {
}

#ifdef UNDEFINED
uint64_t attr_item_impl::get_bit() {
	return m_utils.getBitValue();
}

void attr_item_impl::set_bit(uint64_t v) {
	m_utils.setBitValue(v);
}

int64_t attr_item_impl::get_int() {
	return m_utils.getIntValue();
}

void attr_item_impl::set_int(int64_t v) {
	m_utils.setIntValue(v);
}

method_param_list attr_item_impl::operator,(const attr_item_impl &rhs) {
	method_param_list ret(*this);

	ret = (ret, rhs);

	return ret;
}

exec_stmt attr_item_impl::operator =(const exec_import_call_stmt &rhs) {
	return exec_stmt(new ExecAssignCallStmtImp(
			*this, ExecAssignStmtImp::AssignOp_Eq, rhs));
}

exec_stmt attr_item_impl::operator =(const expr &rhs) {
	return exec_stmt(new ExecAssignExprStmtImp(
			*this, ExecAssignStmtImp::AssignOp_Eq, rhs));
}

exec_stmt attr_item_impl::operator +=(const exec_import_call_stmt &rhs) {
	return exec_stmt(new ExecAssignCallStmtImp(
			*this, ExecAssignStmtImp::AssignOp_PlusEq, rhs));
}

exec_stmt attr_item_impl::operator +=(const expr &rhs) {
	return exec_stmt(new ExecAssignExprStmtImp(
			*this, ExecAssignStmtImp::AssignOp_PlusEq, rhs));
}

exec_stmt attr_item_impl::operator -=(const exec_import_call_stmt &rhs) {
	return exec_stmt(new ExecAssignCallStmtImp(
			*this, ExecAssignStmtImp::AssignOp_MinusEq, rhs));
}

exec_stmt attr_item_impl::operator -=(const expr &rhs) {
	return exec_stmt(new ExecAssignExprStmtImp(
			*this, ExecAssignStmtImp::AssignOp_MinusEq, rhs));
}

exec_stmt attr_item_impl::operator <<=(const exec_import_call_stmt &rhs) {
	return exec_stmt(new ExecAssignCallStmtImp(
			*this, ExecAssignStmtImp::AssignOp_LShiftEq, rhs));
}

exec_stmt attr_item_impl::operator <<=(const expr &rhs) {
	return exec_stmt(new ExecAssignExprStmtImp(
			*this, ExecAssignStmtImp::AssignOp_LShiftEq, rhs));
}

exec_stmt attr_item_impl::operator >>=(const exec_import_call_stmt &rhs) {
	return exec_stmt(new ExecAssignCallStmtImp(
			*this, ExecAssignStmtImp::AssignOp_RShiftEq, rhs));
}

exec_stmt attr_item_impl::operator >>=(const expr &rhs) {
	return exec_stmt(new ExecAssignExprStmtImp(
			*this, ExecAssignStmtImp::AssignOp_RShiftEq, rhs));
}

exec_stmt attr_item_impl::operator |=(const exec_import_call_stmt &rhs) {
	return exec_stmt(new ExecAssignCallStmtImp(
			*this, ExecAssignStmtImp::AssignOp_OrEq, rhs));
}

exec_stmt attr_item_impl::operator |=(const expr &rhs) {
	return exec_stmt(new ExecAssignExprStmtImp(
			*this, ExecAssignStmtImp::AssignOp_OrEq, rhs));
}

exec_stmt attr_item_impl::operator &=(const exec_import_call_stmt &rhs) {
	return exec_stmt(new ExecAssignCallStmtImp(
			*this, ExecAssignStmtImp::AssignOp_AndEq, rhs));
}

exec_stmt attr_item_impl::operator &=(const expr &rhs) {
	return exec_stmt(new ExecAssignExprStmtImp(
			*this, ExecAssignStmtImp::AssignOp_AndEq, rhs));
}

#endif /* UNDEFINED */

} /* namespace vendor */
} /* namespace pss */
