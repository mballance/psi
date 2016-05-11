/*
 * ModelImpl.h
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

class ModelImpl: public IModel {

	public:
		ModelImpl();

		virtual ~ModelImpl();

//		virtual const std::vector<IPackage*> &getPackages();

		virtual IBaseItem::ItemType getType() const {
			return IBaseItem::TypeModel;
		}

		virtual const std::string &getName() const {
			return m_name;
		}

		virtual const std::vector<IBaseItem *> &getItems() const;

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
				uint32_t				msb,
				uint32_t				lsb);

		/**
		 * Action
		 */
		virtual IAction *mkAction(const std::string &name, IAction *super_type);

		virtual IComponent *mkComponent(const std::string &name);

		virtual IStruct *mkStruct(
				const std::string 		&name,
				IStruct::StructType		t,
				IStruct 				*super_type);

		/**
		 * Create a field for use in declaring the contents of an
		 * action or struct data type
		 */
		virtual IField *mkField(
				const std::string		&name,
				IBaseItem				*field_type,
				IField::FieldAttr		attr);

		virtual IBinaryExpr *mkBinExpr(
				IExpr 					*lhs,
				IBinaryExpr::BinOpType	op,
				IExpr 					*rhs);

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


	private:
		std::string					m_name;
		std::vector<IBaseItem *>	m_children;
		PackageImpl					m_global_pkg;
//		std::vector<IPackage *>		m_packages;

};

} /* namespace psi */

#endif /* IMPL_MODELIMPL_H_ */
