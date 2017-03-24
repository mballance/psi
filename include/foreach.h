/*
 * foreach.h
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
 *  Created on: Aug 10, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_FOREACH_H
#define INCLUDED_FOREACH_H
#include <vector>
#include "prv/expr.h"
#include "prv/attr_item.h"
#include "prv/constraint_stmt.h"
#include "prv/activity_stmt.h"

namespace pss {

class foreach : public vendor::foreach_impl {
public:

	template <class... T> foreach(
			const attr_item 								&var,
			const attr_item									&index_var,
			const T&...	/* constraint_stmt|activity_stmt */	stmts);

};

}




#endif /* INCLUDE_CLASSLIB_FOREACH_H_ */
