/*
 * With.h
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
 *  Created on: Jul 15, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_WITH_H
#define INCLUDED_WITH_H

#include "classlib/expr.h"

namespace pss {

class attr_item;
class expr_list;
class With: public expr {
public:
	With(const attr_item &lhs, const expr_list &stmt);

	virtual ~With();
};

} /* namespace pss */

#endif /* INCLUDED_WITH_H */

