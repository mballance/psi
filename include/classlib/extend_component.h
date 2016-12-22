/*
 * extend_component.h
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
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_CLASSLIB_EXTENDCOMPONENT_H_
#define SRC_CLASSLIB_EXTENDCOMPONENT_H_
#include "classlib/extend_base.h"

namespace pss {

template <class T> class extend_component : public extend_base<T> {

	protected:
		extend_component(const scope &p) : extend_base<T>(p) { }

		virtual ~extend_component() { }

};

} /* namespace pss */

#endif /* SRC_CLASSLIB_EXTENDCOMPONENT_H_ */
