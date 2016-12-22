/*
 * ConstraintImp.h
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
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_CONSTRAINT_IMP_H
#define INCLUDED_CONSTRAINT_IMP_H
#include <string>

#include "classlib/constraint.h"
#include "NamedBaseItemImp.h"

namespace pss {

class ConstraintImp : public NamedBaseItemImp {
public:
	ConstraintImp(constraint *master, base_item *p, const expr_list &stmt);

	ConstraintImp(
			constraint				*master,
			base_item 				*p,
			const std::string 		&name,
			const expr_list 			&stmt);

	virtual ~ConstraintImp();

	expr_list &getStmt() {
		return m_stmt;
	}

private:
	expr_list				m_stmt;
};

} /* namespace pss */

#endif /* CONSTRAINT_H_ */
