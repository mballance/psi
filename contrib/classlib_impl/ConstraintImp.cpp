/*
 * ConstraintImp.cpp
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
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "ConstraintImp.h"

namespace pss {

Constraint::Constraint(BaseItem *p, const ExprList &stmt) :
		BaseItem(new ConstraintImp(this, p, "", stmt)) { }

ConstraintImp::ConstraintImp(Constraint *master, BaseItem *p, const ExprList &stmt) :
		NamedBaseItemImp(master, BaseItemImp::TypeConstraint, p), m_stmt(stmt) { }

Constraint::Constraint(BaseItem *p, const std::string &name, const ExprList &stmt) :
		BaseItem(new ConstraintImp(this, p, name, stmt)) { }

ConstraintImp::ConstraintImp(Constraint *master, BaseItem *p, const std::string &name, const ExprList &stmt) :
		NamedBaseItemImp(master, BaseItemImp::TypeConstraint, p, name), m_stmt(stmt) { }

Constraint::~Constraint() {
	// TODO Auto-generated destructor stub
}

ConstraintImp::~ConstraintImp() {
	// TODO Auto-generated destructor stub
}

} /* namespace pss */
