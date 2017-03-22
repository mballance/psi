/*
 * scope.h
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
 *  Created on: Jul 7, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_SCOPE_H
#define INCLUDED_SCOPE_H

#include <string>
// <vendor>
#include "vendor/scope_impl.h"
// </vendor>

namespace pss {

class scope : public pss::vendor::scope_impl {
public:
	template <class T> scope(T *t);

	scope(const char *name);

	virtual ~scope();

};

} /* namespace pss */
// <vendor>
#include "vendor/scope.hpp"
// </vendor>

#endif /* SRC_PSI_CLASSLIB_SCOPE_H_ */
