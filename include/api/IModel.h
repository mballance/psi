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
#include "api/IBind.h"
#include "api/IComponent.h"
#include "api/IConstraint.h"
#include "api/IConstraintBlock.h"
#include "api/IConstraintExpr.h"
#include "api/IConstraintIf.h"
#include "api/IExec.h"
#include "api/IExtend.h"
#include "api/IField.h"
#include "api/IGraphBlockStmt.h"
#include "api/IGraphIfElseStmt.h"
#include "api/IGraphRepeatStmt.h"
#include "api/IGraphTraverseStmt.h"
#include "api/ILiteral.h"
#include "api/IPackage.h"
#include "api/IScalarType.h"
#include "api/IScopeItem.h"
#include "api/IStruct.h"
#include "api/ICallbackContext.h"
#include "api/IItemFactory.h"

namespace psi_api {

	class IModel :
			public virtual IBaseItem,
			public virtual IScopeItem,
			public virtual IItemFactory /* temporary */ {
		public:

			virtual ~IModel() { }

			virtual IPackage *getGlobalPackage() = 0;

			virtual IPackage *findPackage(const std::string &name, bool create=false) = 0;

			virtual IItemFactory *getItemFactory() = 0;

			virtual ICallbackContext *getCallbackContext() = 0;

	};

}



#endif /* SRC_API_IMODEL_H_ */
