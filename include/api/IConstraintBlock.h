/*
 * IConstraintBlock.h
 *
 * Copyright 2016 Mentor Graphics Corporation
 * All Rights Reserved Worldwide
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

#ifndef SRC_PSI_API_ICONSTRAINTBLOCK_H_
#define SRC_PSI_API_ICONSTRAINTBLOCK_H_
#include <vector>
#include <string>

#include "api/IConstraint.h"
#include "api/INamedItem.h"

namespace psi_api {

class IConstraintBlock :
		public virtual IConstraint,
		public virtual INamedItem {

public:

	virtual ~IConstraintBlock() { }

	virtual void add(IConstraint *c) = 0;

	virtual void add(const std::vector<IConstraint *> &cl) = 0;

	virtual const std::vector<IConstraint *> &getConstraints() const = 0;

};
}




#endif /* SRC_PSI_API_ICONSTRAINTBLOCK_H_ */
