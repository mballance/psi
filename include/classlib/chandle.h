/*
 * chandle.h
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
 *  Created on: Apr 29, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_CHANDLE_H
#define INCLUDED_CHANDLE_H
#include "classlib/base_item.h"
#include "classlib/scope.h"
#include "classlib/chandle_type.h"

namespace pss {

template <class T=void> class chandle : public chandle_type {
public:

	chandle(const scope &p) : chandle_type(p) { }

	chandle(const std::string &name) : chandle_type(name) { }

	T *get() { return static_cast<T *>(chandle_type::get()); }

	void set(T *v) { chandle_type::set(v); }

};

} /* namespace pss */

#endif /* SRC_CLASSLIB_CHANDLE_H_ */
