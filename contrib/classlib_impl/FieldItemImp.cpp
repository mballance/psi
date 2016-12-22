/*
 * FieldItem.cpp
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

#include "classlib/Expr.h"
#include "classlib/Scope.h"
#include "BaseItemImp.h"
#include "ExecAssignCallStmtImp.h"
#include "ExecAssignExprStmtImp.h"
#include "ExecAssignStmtImp.h"
#include "ScopeImp.h"
#include "ModelImp.h"

namespace pss {

FieldItem::FieldItem(
		BaseItem				*p,
		const std::string		&name,
		FieldAttr				modifiers,
		const BaseItem			*type_hndl,
		const Expr				*array_dim) : BaseItem(
				new FieldItemImp(this, p, name, array_dim, modifiers, 0, type_hndl->impl())) {

}

FieldItem::FieldItem(
		const Scope				&scope,
		FieldItem::FieldAttr 	modifiers,
		const BaseItem			&type_hndl,
		const Expr				*array_dim) :
		BaseItem(new FieldItemImp(this,
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

FieldItem::FieldItem(
		const Scope				&scope,
		FieldItem::FieldAttr 	modifiers,
		const BaseItem			*type_hndl,
		const Expr				*array_dim) :
		BaseItem(new FieldItemImp(
				this, // master
				ModelImp::global()->getParentScope(), // parent scope
				ModelImp::global()->get_field_name(), // name
				array_dim,
				modifiers,
				0, // wrapper
				(type_hndl)?type_hndl->impl():0)) {

	fprintf(stdout, "FieldItem: scope, modifiers, type_hndl_ptr: %s this=%p\n",
			ModelImp::global()->get_field_name(), this);
	ModelImp::print_scopes();

	FieldItemImp *imp = static_cast<FieldItemImp *>(impl());
	if (imp->getDataType()) {
		imp->getDataType()->inc_refcnt();
	}
}

FieldItemImp::FieldItemImp(
		FieldItem 				*master,
		BaseItem 				*p,
		const std::string 		&name,
		const Expr				*array_dim,
		FieldItem::FieldAttr	attr,
		BaseItem				*wrapper,
		BaseItemImp				*type_hndl) :
	NamedBaseItemImp(master, BaseItemImp::TypeField, p, name),
		m_data_type(0), m_attr(attr), m_internal(false),
		m_has_array_dim(array_dim!=0),
		m_array_dim((array_dim)?array_dim->imp():ExprImp(0)),
		m_utils(this) {

	fprintf(stdout, "FieldItemImp: name=%s parent=%p (%d)\n",
			name.c_str(), p, (p)?p->impl()->getObjectType():-1);

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

FieldItem::~FieldItem() {
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

uint64_t FieldItem::get_bit() {
	return static_cast<FieldItemImp *>(impl())->m_utils.getBitValue();
}

void FieldItem::set_bit(uint64_t v) {
	static_cast<FieldItemImp *>(impl())->m_utils.setBitValue(v);
}

int64_t FieldItem::get_int() {
	return static_cast<FieldItemImp *>(impl())->m_utils.getIntValue();
}

void FieldItem::set_int(int64_t v) {
	static_cast<FieldItemImp *>(impl())->m_utils.setIntValue(v);
}

void FieldItem::setModifiers(FieldAttr modifiers) {
	static_cast<FieldItemImp *>(impl())->setAttr(modifiers);
}

MethodParamList FieldItem::operator,(const FieldItem &rhs) {
	MethodParamList ret(*this);

	ret = (ret, rhs);

	return ret;
}

ExecStmt FieldItem::operator =(const ExecImportCallStmt &rhs) {
	return ExecStmt(new ExecAssignCallStmtImp(
			*this, ExecAssignStmtImp::AssignOp_Eq, rhs));
}

ExecStmt FieldItem::operator =(const Expr &rhs) {
	return ExecStmt(new ExecAssignExprStmtImp(
			*this, ExecAssignStmtImp::AssignOp_Eq, rhs));
}

ExecStmt FieldItem::operator +=(const ExecImportCallStmt &rhs) {
	return ExecStmt(new ExecAssignCallStmtImp(
			*this, ExecAssignStmtImp::AssignOp_PlusEq, rhs));
}

ExecStmt FieldItem::operator +=(const Expr &rhs) {
	return ExecStmt(new ExecAssignExprStmtImp(
			*this, ExecAssignStmtImp::AssignOp_PlusEq, rhs));
}

ExecStmt FieldItem::operator -=(const ExecImportCallStmt &rhs) {
	return ExecStmt(new ExecAssignCallStmtImp(
			*this, ExecAssignStmtImp::AssignOp_MinusEq, rhs));
}

ExecStmt FieldItem::operator -=(const Expr &rhs) {
	return ExecStmt(new ExecAssignExprStmtImp(
			*this, ExecAssignStmtImp::AssignOp_MinusEq, rhs));
}

ExecStmt FieldItem::operator <<=(const ExecImportCallStmt &rhs) {
	return ExecStmt(new ExecAssignCallStmtImp(
			*this, ExecAssignStmtImp::AssignOp_LShiftEq, rhs));
}

ExecStmt FieldItem::operator <<=(const Expr &rhs) {
	return ExecStmt(new ExecAssignExprStmtImp(
			*this, ExecAssignStmtImp::AssignOp_LShiftEq, rhs));
}

ExecStmt FieldItem::operator >>=(const ExecImportCallStmt &rhs) {
	return ExecStmt(new ExecAssignCallStmtImp(
			*this, ExecAssignStmtImp::AssignOp_RShiftEq, rhs));
}

ExecStmt FieldItem::operator >>=(const Expr &rhs) {
	return ExecStmt(new ExecAssignExprStmtImp(
			*this, ExecAssignStmtImp::AssignOp_RShiftEq, rhs));
}

ExecStmt FieldItem::operator |=(const ExecImportCallStmt &rhs) {
	return ExecStmt(new ExecAssignCallStmtImp(
			*this, ExecAssignStmtImp::AssignOp_OrEq, rhs));
}

ExecStmt FieldItem::operator |=(const Expr &rhs) {
	return ExecStmt(new ExecAssignExprStmtImp(
			*this, ExecAssignStmtImp::AssignOp_OrEq, rhs));
}

ExecStmt FieldItem::operator &=(const ExecImportCallStmt &rhs) {
	return ExecStmt(new ExecAssignCallStmtImp(
			*this, ExecAssignStmtImp::AssignOp_AndEq, rhs));
}

ExecStmt FieldItem::operator &=(const Expr &rhs) {
	return ExecStmt(new ExecAssignExprStmtImp(
			*this, ExecAssignStmtImp::AssignOp_AndEq, rhs));
}

} /* namespace pss */
