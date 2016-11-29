/*
 * ModelImpl.h
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
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef IMPL_MODELIMPL_H_
#define IMPL_MODELIMPL_H_
#include "PackageImpl.h"
#include "api/ILiteral.h"
#include "api/IModel.h"
#include "api/IStruct.h"

using namespace psi_api;

namespace psi {

class ModelImpl:
		public virtual IModel,
		public virtual BaseItemImpl {

	public:
		ModelImpl();

		virtual ~ModelImpl();

//		virtual const std::vector<IPackage*> &getPackages();

		virtual IBaseItem::ItemType getType() const {
			return IBaseItem::TypeModel;
		}

		virtual IBaseItem *clone() { return 0; }

		virtual IBaseItem *clone(IBaseItem *item);

		virtual IBaseItem *getParent() const { return 0; }

		void setParent(IBaseItem *p) { }

		virtual const std::vector<IBaseItem *> &getItems() const;

		virtual void remove(IBaseItem *it);

		virtual void add(IBaseItem *it);

		virtual IPackage *getGlobalPackage();

		virtual IPackage *findPackage(const std::string &name, bool create=false);

		/**
		 * Data Types
		 */

		/**
		 * Creates a scalar type. The msb and lsb parameters are ignored for types
		 * other than Int and Bit
		 */
		virtual IScalarType *mkScalarType(
				IScalarType::ScalarType t,
				IExpr					*msb,
				IExpr					*lsb);

		/**
		 * Action
		 */
		virtual IAction *mkAction(const std::string &name, IAction *super_type);

		virtual IBind *mkBind(const std::vector<IBindPath *> &targets);

		virtual IBindPath *mkBindPath(const std::vector<IBaseItem *> &path);

		virtual IComponent *mkComponent(const std::string &name);

		virtual IExec *mkTargetTemplateExec(
				IExec::ExecKind			kind,
				const std::string		&language,
				const std::string		&text);

		virtual IExec *mkInlineExec(
				IExec::ExecKind			kind,
				IExecCallback				*exec);

		virtual IExec *mkNativeExec(
				IExec::ExecKind					kind,
				const std::vector<IExecStmt *>	&stmts);

		virtual IExecExprStmt *mkExecExprStmt(
				IFieldRef				*field,
				IExecStmt::AssignOp		op,
				IExpr					*rhs);

		virtual IExecCallStmt *mkExecCallStmt(
				IFieldRef					*target,
				IExecStmt::AssignOp			op,
				IImportFunc					*func,
				const std::vector<IExpr *>	&parameters);

		virtual IStruct *mkStruct(
				const std::string 		&name,
				IStruct::StructType		t,
				IStruct 				*super_type);

		virtual IExtend *mkExtend(IBaseItem *target);

		/**
		 * Create a field for use in declaring the contents of an
		 * action or struct data type
		 */
		virtual IField *mkField(
				const std::string		&name,
				IBaseItem				*field_type,
				IField::FieldAttr		attr,
				IExpr					*array_dim);

		virtual IGraphBlockStmt *mkGraphBlockStmt(
				IGraphStmt::GraphStmtType type=IGraphStmt::GraphStmt_Block);

		virtual IGraphTraverseStmt *mkGraphTraverseStmt(
				IFieldRef *action, IConstraint *with_c=0);

		virtual IGraphRepeatStmt *mkGraphRepeatStmt(
				IGraphRepeatStmt::RepeatType type,
				IExpr *expr, IGraphStmt *body);


		virtual IBinaryExpr *mkBinExpr(
				IExpr 					*lhs,
				IBinaryExpr::BinOpType	op,
				IExpr 					*rhs);

		virtual IFieldRef *mkFieldRef(
				const std::vector<IField *>		&field_path);

		virtual ILiteral *mkIntLiteral(int64_t v);

		virtual ILiteral *mkBitLiteral(uint64_t v);

		virtual ILiteral *mkBoolLiteral(bool v);

		virtual ILiteral *mkStringLiteral(const std::string &v);

		virtual IConstraintBlock *mkConstraintBlock(
				const std::string 		&name,
				IConstraint				*c);

		virtual IConstraintBlock *mkConstraintBlock(
				const std::string 					&name,
				const std::vector<IConstraint *>	&cl);

		virtual IConstraintExpr *mkConstraintExpr(IExpr *expr);

		virtual IConstraintIf *mkConstraintIf(
				IExpr 			*cond,
				IConstraint 	*true_c,
				IConstraint 	*false_c);

		virtual IConstraintImplies *mkConstraintImplies(
				IExpr			*cond,
				IConstraint		*imp);

		virtual IImportFunc *mkImportFunc(
				const std::string				&name,
				IBaseItem						*ret_type,
				const std::vector<IField *>		&parameters);

		virtual IItemFactory *getItemFactory() { return this; }

		virtual ICallbackContext *getCallbackContext();

		virtual void setCallbackContext(ICallbackContext *ctxt);

		/**
		 * Null implementation
		 */
		virtual IField *getField(const std::string &name) { return 0; }

		virtual const std::string &getAttribute(const std::string &key);

		virtual void getAttributes(std::vector<std::string> &keys);

		virtual bool hasAttribute(const std::string &key);

		virtual void setAttribute(const std::string &key, const std::string &val);

		virtual void clearAttribute(const std::string &key);


	private:
		std::vector<IBaseItem *>	m_children;
		PackageImpl					m_global_pkg;
		ICallbackContext			*m_callback_ctxt;
		std::string					m_null_attr;


};

} /* namespace psi */

#endif /* IMPL_MODELIMPL_H_ */
