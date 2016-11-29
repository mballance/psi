/*
 * ModelImpl.cpp
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
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#include "ModelImpl.h"

#include <stdio.h>
#include <stdlib.h>
#include <iterator>
#include <string>
#include <vector>
#include <assert.h>

#include "ActionImpl.h"
#include "BinaryExprImpl.h"
#include "BindImpl.h"
#include "BindPathImpl.h"
#include "ComponentImpl.h"
#include "ConstraintBlockImpl.h"
#include "ConstraintExprImpl.h"
#include "ConstraintIfImpl.h"
#include "ConstraintImpliesImpl.h"
#include "ExecImpl.h"
#include "ExecCallStmtImpl.h"
#include "ExecExprStmtImpl.h"
#include "ExtendImpl.h"
#include "FieldImpl.h"
#include "FieldRefImpl.h"
#include "GraphBlockStmtImpl.h"
#include "GraphRepeatStmtImpl.h"
#include "GraphTraverseStmtImpl.h"
#include "ImportFuncImpl.h"
#include "LiteralImpl.h"
#include "ScalarTypeImpl.h"
#include "StructImpl.h"
#include "api/IBaseItem.h"
#if !defined(_WIN32) && !defined(__CYGWIN__)
#include <execinfo.h>
#endif

namespace psi {

ModelImpl::ModelImpl() :
		BaseItemImpl(IBaseItem::TypeModel),
		m_global_pkg(""), m_callback_ctxt(0) {
}

ModelImpl::~ModelImpl() {
	// TODO Auto-generated destructor stub
}

//const std::vector<IPackage*> &ModelImpl::getPackages() {
//	return m_packages;
//}

const std::vector<IBaseItem *> &ModelImpl::getItems() const {
	return m_children;
}

void ModelImpl::remove(IBaseItem *it) {
	for (std::vector<IBaseItem *>::iterator i=m_children.begin();
			i!=m_children.end(); i++) {
		if ((*i) == it) {
			m_children.erase(i);
			break;
		}
	}
}


void ModelImpl::add(IBaseItem *it) {
	if (it) {
		it->setParent(this);
		m_children.push_back(it);
	} else {
		fprintf(stdout, "Error: Attempting to add null item\n");
#if !defined(_WIN32) && !defined(__CYGWIN__)
		{
			int bt_sz;
			void *bt[256];
			bt_sz = backtrace(bt, sizeof(bt)/sizeof(void *));

			char **bt_s = backtrace_symbols(bt, bt_sz);
			fprintf(stdout, "Backtrace:\n");
			for (int i=0; i<bt_sz; i++) {
				fprintf(stdout, "  %s\n", bt_s[i]);
			}
			free(bt_s);
		}
#endif
	}
}

IPackage *ModelImpl::getGlobalPackage() {
	return &m_global_pkg;
}

IPackage *ModelImpl::findPackage(const std::string &name, bool create) {
	std::vector<IBaseItem *>::iterator it;

	for (it=m_children.begin(); it!=m_children.end(); it++) {
		if ((*it)->getType() == IBaseItem::TypePackage) {
			IBaseItem *bi = *it;
			IPackage *pkg = dynamic_cast<IPackage *>(bi);
			if (pkg->getName() == name) {
				return pkg;
			}
		}
	}

	if (create) {
		IPackage *pkg = new PackageImpl(name);
		m_children.push_back(pkg);
		return pkg;
	} else {
		return 0;
	}
}

/**
 * Data Types
 */

/**
 * Creates a scalar type. The msb and lsb parameters are ignored for types
 * other than Int and Bit
 */
IScalarType *ModelImpl::mkScalarType(
		IScalarType::ScalarType t,
		IExpr					*msb,
		IExpr					*lsb) {
	if (t != IScalarType::ScalarType_Bit && t != IScalarType::ScalarType_Int) {
		msb = 0;
		lsb = 0;
	}
	return new ScalarTypeImpl(t, msb, lsb);
}

IBind *ModelImpl::mkBind(const std::vector<IBindPath *> &targets) {
	return new BindImpl(targets);
}

IBindPath *ModelImpl::mkBindPath(const std::vector<IBaseItem *> &path) {
	return new BindPathImpl(path);
}

/**
 * Action
 */
IAction *ModelImpl::mkAction(const std::string &name, IAction *super_type) {
	return new ActionImpl(name, super_type);
}

IComponent *ModelImpl::mkComponent(const std::string &name) {
	return new ComponentImpl(name);
}

IExec *ModelImpl::mkTargetTemplateExec(
		IExec::ExecKind			kind,
		const std::string		&language,
		const std::string		&text) {
	return new ExecImpl(kind, language, text);
}

IExec *ModelImpl::mkInlineExec(
		IExec::ExecKind			kind,
		IExecCallback				*exec) {
	return new ExecImpl(kind, exec);
}

IExec *ModelImpl::mkNativeExec(
		IExec::ExecKind					kind,
		const std::vector<IExecStmt *>	&stmts) {
	return new ExecImpl(kind, stmts);
}

IExecExprStmt *ModelImpl::mkExecExprStmt(
		IFieldRef				*target,
		IExecStmt::AssignOp		op,
		IExpr					*rhs) {
	return new ExecExprStmtImpl(target, op, rhs);
}

IExecCallStmt *ModelImpl::mkExecCallStmt(
		IFieldRef					*target,
		IExecStmt::AssignOp			op,
		IImportFunc					*func,
		const std::vector<IExpr *>	&parameters) {
	return new ExecCallStmtImpl(target, op, func, parameters);
}

IStruct *ModelImpl::mkStruct(
		const std::string 		&name,
		IStruct::StructType		t,
		IStruct 				*super_type) {
	return new StructImpl(name, t, super_type);
}

IExtend *ModelImpl::mkExtend(IBaseItem *target) {
	return new ExtendImpl(target);
}

/**
 * Create a field for use in declaring the contents of an
 * action or struct data type
 */
IField *ModelImpl::mkField(
		const std::string		&name,
		IBaseItem				*field_type,
		IField::FieldAttr		attr,
		IExpr					*array_dim) {
	return new FieldImpl(name, field_type, attr, array_dim);
}

IGraphBlockStmt *ModelImpl::mkGraphBlockStmt(IGraphStmt::GraphStmtType type) {
	return new GraphBlockStmtImpl(type);
}

IGraphRepeatStmt *ModelImpl::mkGraphRepeatStmt(
		IGraphRepeatStmt::RepeatType type,
		IExpr *expr, IGraphStmt *body) {
	return new GraphRepeatStmtImpl(type, expr, body);
}

IGraphTraverseStmt *ModelImpl::mkGraphTraverseStmt(
		IFieldRef *action, IConstraint *with_c) {
	return new GraphTraverseStmtImpl(action, with_c);
}

IBinaryExpr *ModelImpl::mkBinExpr(
		IExpr 					*lhs,
		IBinaryExpr::BinOpType	op,
		IExpr 					*rhs) {
	return new BinaryExprImpl(lhs, op, rhs);
}

IFieldRef *ModelImpl::mkFieldRef(
		const std::vector<IField *>		&field_path) {
	return new FieldRefImpl(field_path);
}

ILiteral *ModelImpl::mkIntLiteral(int64_t v) {
	return new LiteralImpl(v);
}

ILiteral *ModelImpl::mkBitLiteral(uint64_t v) {
	return new LiteralImpl(v);
}

ILiteral *ModelImpl::mkBoolLiteral(bool v) {
	return new LiteralImpl(v);
}

ILiteral *ModelImpl::mkStringLiteral(const std::string &v) {
	return new LiteralImpl(v);
}

IConstraintBlock *ModelImpl::mkConstraintBlock(
		const std::string 		&name,
		IConstraint				*c) {
	IConstraintBlock *ret = new ConstraintBlockImpl(name);

	if (c) {
		ret->add(c);
	}

	return ret;
}

IConstraintBlock *ModelImpl::mkConstraintBlock(
		const std::string 					&name,
		const std::vector<IConstraint *>	&cl) {
	IConstraintBlock *ret = new ConstraintBlockImpl(name);

	ret->add(cl);

	return ret;
}

IConstraintExpr *ModelImpl::mkConstraintExpr(IExpr *expr) {
	return new ConstraintExprImpl(expr);
}


IConstraintIf *ModelImpl::mkConstraintIf(
		IExpr 			*cond,
		IConstraint 	*true_c,
		IConstraint 	*false_c) {
	return new ConstraintIfImpl(cond, true_c, false_c);
}

IConstraintImplies *ModelImpl::mkConstraintImplies(
				IExpr			*cond,
				IConstraint		*imp) {
	return new ConstraintImpliesImpl(cond, imp);
}

IImportFunc *ModelImpl::mkImportFunc(
		const std::string				&name,
		IBaseItem						*ret_type,
		const std::vector<IField *>		&parameters) {
	return new ImportFuncImpl(name, ret_type, parameters);
}

ICallbackContext *ModelImpl::getCallbackContext() {
	if (!m_callback_ctxt) {
		fprintf(stdout, "Error: getCallbackContext returning null handle\n");
		fflush(stdout);
	}
	return m_callback_ctxt;
}

void ModelImpl::setCallbackContext(ICallbackContext *ctxt) {
	m_callback_ctxt = ctxt;
}

IBaseItem *ModelImpl::clone(IBaseItem *item) {
	switch (item->getType()) {
	case TypeAction:
		return ActionImpl::clone(this, dynamic_cast<IAction *>(item));
	case TypeBind:
	case TypeComponent:
	case TypeConstraint:
	case TypeField:
	case TypeImport:
	case TypeExec:
	case TypeExtend:
	case TypeGraphStmt:
	case TypeImportFunc:
	case TypeModel:
	case TypeObject:
	case TypePackage:
	case TypeScalar:
	case TypeStruct:
	case TypeSymbol:
	default:
		break;
	}

	return 0;
}

const std::string &ModelImpl::getAttribute(const std::string &key) {
	return m_null_attr;
}

void ModelImpl::getAttributes(std::vector<std::string> &keys) {
	keys.clear();
}

bool ModelImpl::hasAttribute(const std::string &key) {
	return false;
}

void ModelImpl::setAttribute(const std::string &key, const std::string &val) {

}

void ModelImpl::clearAttribute(const std::string &key) {

}


} /* namespace psi */
