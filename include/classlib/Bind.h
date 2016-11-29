/*
 * Bind.h
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
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_BIND_H
#define INCLUDED_BIND_H
#include <vector>
#include <functional>
#include "classlib/BaseItem.h"
#include "classlib/Types.h"

namespace pss {

class Bind: public BaseItem {
public:
	Bind(BaseItem *p, BaseItem &i1, BaseItem &i2);

	Bind(BaseItem *p, BaseItem &i1, BaseItem &i2, BaseItem &i3);

	Bind(BaseItem *p, BaseItem &i1, BaseItem &i2, BaseItem &i3, BaseItem &i4);

	Bind(BaseItem *p, BaseItem &i1, BaseItem &i2, BaseItem &i3, BaseItem &i4, BaseItem &i5);

	Bind(BaseItem *p, const std::vector<BaseItem *> &items);

	virtual ~Bind();

protected:


};

} /* namespace pss */

#endif /* INCLUDED_BIND_H */
