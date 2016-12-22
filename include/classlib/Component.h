/*
 * component.h
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

#ifndef COMPONENT_H_
#define COMPONENT_H_
#include <string>

#include "classlib/base_item.h"
#include "classlib/scope.h"
#include "classlib/attr_item.h"

namespace pss {

class component : public base_item {

	public:

		virtual ~component();

		operator attr_item &() const;

	protected:

		component(const scope &p);

//TODO:		operator const attr_item &() const;

};

} /* namespace pss */

#endif /* COMPONENT_H_ */
