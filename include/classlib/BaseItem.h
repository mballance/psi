/*
 * BaseItem.h
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

#include "classlib/Expr.h"
#include "classlib/ExprList.h"
#include "classlib/ExprListBuilder.h"

namespace pss {

class BaseItemImp;
class BaseItem {
public:
	friend BaseItemImp;

	BaseItem *operator ()();

	Expr operator [] (const Expr &rhs);

	Expr operator [] (const std::string &idx);

//	Expr operator -> (const Expr &rhs);

	ExprListBuilder operator,(const BaseItem &rhs);

	Expr operator = (const Expr &rhs);

	virtual ~BaseItem();

	BaseItemImp *impl() const;

	BaseItem(const BaseItem &rhs);

protected:

		BaseItem(BaseItemImp *impl);


protected:
		BaseItemImp				*m_impl;

};

} /* namespace pss */

#endif /* INCLUDED_BASE_ITEM_H */
