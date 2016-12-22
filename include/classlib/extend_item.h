/*
 * extend_item.h
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
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_CLASSLIB_EXTENDITEM_H_
#define SRC_PSI_CLASSLIB_EXTENDITEM_H_

#include "classlib/base_item.h"
#include "classlib/scope.h"

namespace pss {

class extend_item: public base_item {
public:
	extend_item(
			const scope 		&p,
			base_item			*type_hndl,
			base_item			*ext_hndl);

	virtual ~extend_item();

};

} /* namespace pss */

#endif /* SRC_PSI_CLASSLIB_EXTENDITEM_H_ */
