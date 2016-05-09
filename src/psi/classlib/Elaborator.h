/*
 * PsiElaborator.h
 *
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
 *  Created on: May 2, 2016
 *      Author: ballance
 */

#ifndef SRC_ELABORATOR_ELABORATOR_H_
#define SRC_ELABORATOR_ELABORATOR_H_
#include <vector>

#include "api/IAction.h"
#include "api/IConstraint.h"
#include "api/IConstraintIf.h"
#include "api/IExpr.h"
#include "api/IModel.h"
#include "api/IPackage.h"
#include "classlib/Action.h"
#include "classlib/Component.h"
#include "classlib/Constraint.h"
#include "classlib/Package.h"
#include "classlib/Type.h"
#include "classlib/Struct.h"
#include "classlib/ExprCoreIf.h"

using namespace psi_api;

namespace psi {

class Elaborator {
public:

	Elaborator();

	virtual ~Elaborator();

	void elaborate(Type *root, IModel *model);

protected:

	IAction *elaborate_action(Action *a);

	IComponent *elaborate_component(Component *c);

	IConstraint *elaborate_constraint(Constraint *c);

	IConstraintIf *elaborate_constraint_if(ExprCoreIf *if_c);

	IExpr *elaborate_expr(ExprCore *e);

	IConstraint *elaborate_constraint_stmt(ExprCore *s);

	IStruct *elaborate_struct(Struct *str);

	void elaborate_package(IModel *model, Package *pkg_cl);

	IBaseItem *elaborate_struct_action_body_item(Type *t);

private:

	void error(const std::string &msg);

private:
	IModel					*m_model;



};

} /* namespace psi */

#endif /* SRC_ELABORATOR_ELABORATOR_H_ */
