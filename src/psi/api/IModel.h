/*
 * IModel.h
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

#ifndef SRC_API_IMODEL_H_
#define SRC_API_IMODEL_H_
#include <vector>
#include <string>

#include "api/IAction.h"
#include "api/IBaseItem.h"
#include "api/IBinaryExpr.h"
#include "api/IComponent.h"
#include "api/IConstraint.h"
#include "api/IConstraintBlock.h"
#include "api/IConstraintExpr.h"
#include "api/IConstraintIf.h"
#include "api/IExtend.h"
#include "api/IField.h"
#include "api/ILiteral.h"
#include "api/IPackage.h"
#include "api/IScalarType.h"
#include "api/IScopeItem.h"
#include "api/IStruct.h"

namespace psi_api {

	class IModel : public IScopeItem {
		public:

			virtual ~IModel() { }

			virtual IPackage *getGlobalPackage() = 0;

			virtual IPackage *findPackage(const std::string &name, bool create=false) = 0;

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
					uint32_t				lsb) = 0;

			/**
			 * Action
			 */
			virtual IAction *mkAction(const std::string &name, IAction *super_type) = 0;

			/**
			 * Create a new component type
			 */
			virtual IComponent *mkComponent(const std::string &name) = 0;

			/**
			 * Create a new struct type
			 */
			virtual IStruct *mkStruct(
					const std::string 		&name,
					IStruct::StructType		t,
					IStruct 				*super_type) = 0;

			virtual IExtend *mkExtend(IBaseItem	*target) = 0;

			/**
			 * Create a field for use in declaring the contents of an
			 * action or struct data type
			 */
			virtual IField *mkField(
					const std::string		&name,
					IBaseItem				*field_type,
					IField::FieldAttr		attr=IField::FieldAttr_None) = 0;

			virtual IBinaryExpr *mkBinExpr(
					IExpr 					*lhs,
					IBinaryExpr::BinOpType	op,
					IExpr 					*rhs) = 0;

			virtual IFieldRef *mkFieldRef(
					const std::vector<IField *>		&field_path) = 0;

			virtual ILiteral *mkIntLiteral(int64_t v) = 0;

			virtual ILiteral *mkBitLiteral(uint64_t v) = 0;

			virtual ILiteral *mkBoolLiteral(bool v) = 0;

			virtual ILiteral *mkStringLiteral(const std::string &v) = 0;

			/**
			 * Construct a new constraint block. The constraint block is
			 * anonymous if name="". The specified constraint will be
			 * added to the block if it is non-null
			 */
			virtual IConstraintBlock *mkConstraintBlock(
					const std::string 	&name,
					IConstraint			*c=0) = 0;

			/**
			 * Construct a new constraint block, with a list of constraints
			 */
			virtual IConstraintBlock *mkConstraintBlock(
					const std::string 					&name,
					const std::vector<IConstraint *>	&cl) = 0;

			virtual IConstraintExpr *mkConstraintExpr(IExpr *expr) = 0;

			virtual IConstraintIf *mkConstraintIf(
					IExpr 			*cond,
					IConstraint 	*true_c,
					IConstraint 	*false_c) = 0;

	};

}



#endif /* SRC_API_IMODEL_H_ */
