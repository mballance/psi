/*
 * attr_item.cpp
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

#include "FieldItemImp.h"

#include "classlib/expr.h"
#include "classlib/scope.h"
#include "BaseItemImp.h"
#include "ExecAssignCallStmtImp.h"
#include "ExecAssignExprStmtImp.h"
#include "ExecAssignStmtImp.h"
#include "ScopeImp.h"
#include "ModelImp.h"

namespace pss {

attr_item::attr_item(
		base_item				*p,
		const std::string		&name,
		FieldAttr				modifiers,
		const base_item			*type_hndl,
		const expr				*array_dim) : base_item(
				new FieldItemImp(this, p, name, array_dim, modifiers, 0, type_hndl->impl())) {

}

attr_item::attr_item(
		const scope				&scope,
		attr_item::FieldAttr 	modifiers,
		const base_item			&type_hndl,
		const expr				*array_dim) :
		base_item(new FieldItemImp(this,
				ModelImp::global()->getParentScope(),
				ModelImp::global()->get_field_name(),
				array_dim,
				modifiers,
				0,
				type_hndl.impl())) {
	FieldItemImp *imp = static_cast<FieldItemImp *>(impl());
	if (imp->getDataType()) {
		imp->getDataType()->inc_refcnt();
	}
}

attr_item::attr_item(
		const scope				&scope,
		attr_item::FieldAttr 	modifiers,
		const base_item			*type_hndl,
		const expr				*array_dim) :
		base_item(new FieldItemImp(
				this, // master
				ModelImp::global()->getParentScope(), // parent scope
				ModelImp::global()->get_field_name(), // name
				array_dim,
				modifiers,
				0, // wrapper
				(type_hndl)?type_hndl->impl():0)) {

	FieldItemImp *imp = static_cast<FieldItemImp *>(impl());
	if (imp->getDataType()) {
		imp->getDataType()->inc_refcnt();
	}
}

FieldItemImp::FieldItemImp(
		attr_item 				*master,
		base_item 				*p,
		const std::string 		&name,
		const expr				*array_dim,
		attr_item::FieldAttr	attr,
		base_item				*wrapper,
		BaseItemImp				*type_hndl) :
	NamedBaseItemImp(master, BaseItemImp::TypeField, p, name),
		m_data_type(0), m_attr(attr), m_internal(false),
		m_has_array_dim(array_dim!=0),
		m_array_dim((array_dim)?array_dim->imp():ExprImp(0)),
		m_utils(this) {

	// TODO:
	setDataType(type_hndl); // (type_hndl)?type_hndl:wrapper);
	NamedBaseItemImp *wrapper_ni = 0;

	if (wrapper) {
		dynamic_cast<NamedBaseItemImp *>(wrapper->impl());
	}

	// Change the name of the field base-class object to match the field name
	if (wrapper_ni) {
		wrapper_ni->setName(name);
	}

	// re-home the field base-class object
	if (wrapper) {
		toImp(wrapper)->setParent(p);
	}
}

attr_item::~attr_item() {
	FieldItemImp *imp = static_cast<FieldItemImp *>(impl());
	if (imp->getDataType()) {
		imp->getDataType()->inc_refcnt();
	}
}

FieldItemImp::~FieldItemImp() {
	// TODO Auto-generated destructor stub
}

void FieldItemImp::setDataType(BaseItemImp *dt) {
	m_data_type = dt;
}

uint64_t attr_item::get_bit() {
	return static_cast<FieldItemImp *>(impl())->m_utils.getBitValue();
}

void attr_item::set_bit(uint64_t v) {
	static_cast<FieldItemImp *>(impl())->m_utils.setBitValue(v);
}

int64_t attr_item::get_int() {
	return static_cast<FieldItemImp *>(impl())->m_utils.getIntValue();
}

void attr_item::set_int(int64_t v) {
	static_cast<FieldItemImp *>(impl())->m_utils.setIntValue(v);
}

void attr_item::setModifiers(FieldAttr modifiers) {
	static_cast<FieldItemImp *>(impl())->setAttr(modifiers);
}

method_param_list attr_item::operator,(const attr_item &rhs) {
	method_param_list ret(*this);

	ret = (ret, rhs);

	return ret;
}

exec_stmt attr_item::operator =(const exec_import_call_stmt &rhs) {
	return exec_stmt(new ExecAssignCallStmtImp(
			*this, ExecAssignStmtImp::AssignOp_Eq, rhs));
}

exec_stmt attr_item::operator =(const expr &rhs) {
	return exec_stmt(new ExecAssignExprStmtImp(
			*this, ExecAssignStmtImp::AssignOp_Eq, rhs));
}

exec_stmt attr_item::operator +=(const exec_import_call_stmt &rhs) {
	return exec_stmt(new ExecAssignCallStmtImp(
			*this, ExecAssignStmtImp::AssignOp_PlusEq, rhs));
}

exec_stmt attr_item::operator +=(const expr &rhs) {
	return exec_stmt(new ExecAssignExprStmtImp(
			*this, ExecAssignStmtImp::AssignOp_PlusEq, rhs));
}

exec_stmt attr_item::operator -=(const exec_import_call_stmt &rhs) {
	return exec_stmt(new ExecAssignCallStmtImp(
			*this, ExecAssignStmtImp::AssignOp_MinusEq, rhs));
}

exec_stmt attr_item::operator -=(const expr &rhs) {
	return exec_stmt(new ExecAssignExprStmtImp(
			*this, ExecAssignStmtImp::AssignOp_MinusEq, rhs));
}

exec_stmt attr_item::operator <<=(const exec_import_call_stmt &rhs) {
	return exec_stmt(new ExecAssignCallStmtImp(
			*this, ExecAssignStmtImp::AssignOp_LShiftEq, rhs));
}

exec_stmt attr_item::operator <<=(const expr &rhs) {
	return exec_stmt(new ExecAssignExprStmtImp(
			*this, ExecAssignStmtImp::AssignOp_LShiftEq, rhs));
}

exec_stmt attr_item::operator >>=(const exec_import_call_stmt &rhs) {
	return exec_stmt(new ExecAssignCallStmtImp(
			*this, ExecAssignStmtImp::AssignOp_RShiftEq, rhs));
}

exec_stmt attr_item::operator >>=(const expr &rhs) {
	return exec_stmt(new ExecAssignExprStmtImp(
			*this, ExecAssignStmtImp::AssignOp_RShiftEq, rhs));
}

exec_stmt attr_item::operator |=(const exec_import_call_stmt &rhs) {
	return exec_stmt(new ExecAssignCallStmtImp(
			*this, ExecAssignStmtImp::AssignOp_OrEq, rhs));
}

exec_stmt attr_item::operator |=(const expr &rhs) {
	return exec_stmt(new ExecAssignExprStmtImp(
			*this, ExecAssignStmtImp::AssignOp_OrEq, rhs));
}

exec_stmt attr_item::operator &=(const exec_import_call_stmt &rhs) {
	return exec_stmt(new ExecAssignCallStmtImp(
			*this, ExecAssignStmtImp::AssignOp_AndEq, rhs));
}

exec_stmt attr_item::operator &=(const expr &rhs) {
	return exec_stmt(new ExecAssignExprStmtImp(
			*this, ExecAssignStmtImp::AssignOp_AndEq, rhs));
}

} /* namespace pss */
