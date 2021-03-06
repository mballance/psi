/*
 * pss_int.h
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
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#ifndef INT_H_
#define INT_H_
#include "classlib/int_type.h"
#include "classlib/scope.h"
#include "classlib/expr.h"

namespace pss {

class pss_int : public int_type {

	public:

		pss_int() : int_type(0, 31, 0) { }

		pss_int(uint32_t width) : int_type(0, width-1, 0) { }

		pss_int(const std::string &name, uint32_t width) :
			int_type(name, width-1, 0) { }

		pss_int(const scope &parent);


};

}



#endif /* INT_H_ */
