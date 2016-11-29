/*
 * IConstraint.h
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
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_ICONSTRAINT_H_
#define SRC_PSI_API_ICONSTRAINT_H_
#include "IBaseItem.h"

namespace psi_api {

class IConstraint :
		public virtual IBaseItem {
public:

	enum ConstraintType {
		ConstraintType_Block,
		ConstraintType_Expr,
		ConstraintType_If,
		ConstraintType_Implies
	};

public:

	virtual ~IConstraint() { }

	virtual ConstraintType getConstraintType() const = 0;


};

}




#endif /* SRC_PSI_API_ICONSTRAINT_H_ */
