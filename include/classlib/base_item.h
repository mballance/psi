/*
 * base_item.h
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

#ifndef INCLUDED_BASE_ITEM_H
#define INCLUDED_BASE_ITEM_H
#include <string>
#include <vector>

#include "classlib/expr.h"
#include "classlib/expr_list.h"
#include "classlib/expr_list_builder.h"

namespace pss {

class BaseItemImp;
class base_item {
public:
	friend class BaseItemImp;

	base_item *operator ()();

	expr operator [] (const expr &rhs);

	expr operator [] (const std::string &idx);

//	expr operator -> (const expr &rhs);

	expr_list_builder operator,(const base_item &rhs);

	expr operator = (const expr &rhs);

	virtual ~base_item();

	BaseItemImp *impl() const;

	base_item(const base_item &rhs);

protected:

		base_item(BaseItemImp *impl);


protected:
		BaseItemImp				*m_impl;

};

} /* namespace pss */

#endif /* INCLUDED_BASE_ITEM_H */
