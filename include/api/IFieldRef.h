/*
 * IFieldRef.h
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
 *  Created on: May 9, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IFIELDREF_H_
#define SRC_PSI_API_IFIELDREF_H_
#include <vector>
#include "api/IExpr.h"

namespace psi_api {

class IField;
class IFieldRef : public IExpr {

public:

	virtual ~IFieldRef() { }

	/**
	 * Returns a list of field refs that form the field-reference expression
	 * a.b.c, for example, where a is a field of type A, b is a field of type B, etc
	 * would be as follows:
	 * { a-field declared within type A, b-field declared within type B, etc }
	 */
	virtual const std::vector<IField * > &getFieldPath() const = 0;

};


}




#endif /* SRC_PSI_API_IFIELDREF_H_ */
