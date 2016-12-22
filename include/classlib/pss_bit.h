/*
 * pss_bit.h
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
 *  Created on: Apr 25, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_BIT_H
#define INCLUDED_BIT_H
#include "classlib/bit_type.h"
#include "classlib/scope.h"
#include "classlib/pss_types.h"

namespace pss {

class pss_bit : public bit_type {

	public:
		pss_bit() : bit_type(0, 0, 0) { }

		pss_bit(uint32_t width) : bit_type(0, width-1, 0) { }

		pss_bit(const char *name) : bit_type(name, 0, 0) { }

		pss_bit(const std::string &name) : bit_type(name, 0, 0) { }

		virtual ~pss_bit() { }
};

} /* namespace pss */

#endif /* SRC_BIT_H_ */
