/*
 * export_item.h
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
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_EXPORT_ITEM_H
#define INCLUDED_EXPORT_ITEM_H

#include "classlib/base_item.h"
#include "classlib/pss_types.h"
#include "classlib/action.h"
#include "classlib/expr_list.h"

namespace pss {

class export_item: public base_item {
public:
	export_item(base_item *p);

	export_item(base_item *p, const expr_list &exp_params);

	virtual ~export_item();

	void setDataType(base_item *t);

};

}

#endif /* SRC_PSI_CLASSLIB_EXPORTACTION_H_ */
