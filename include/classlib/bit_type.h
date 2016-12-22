/*
 * bit_type.h
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
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_BIT_TYPE_H
#define INCLUDED_BIT_TYPE_H
#include <stdint.h>
#include <string>

#include "classlib/base_item.h"
#include "classlib/pss_types.h"

namespace pss {

class expr_list;
class bit_type : public base_item {

	public:
		bit_type(
				base_item 			*p,
				uint32_t			msb,
				uint32_t			lsb);

		bit_type(
				const std::string	&name,
				uint32_t			msb,
				uint32_t			lsb);

		virtual ~bit_type();

		/**
		 * The get method returns the solve-time value of this
		 * data field. Calling this method is only valid
		 * on fields of this type, and only from within an
		 * inline-exec callback.
		 */
		uint64_t get();

		/**
		 * The set method sets the value of this data field.
		 * Calling this method is only valid on fields
		 * of this type, and only from within an
		 * inline-exec callback.
		 */
		void set(uint64_t v);

		expr inside(const expr_list &inside_l);

#ifdef PSS_HAVE_CXX_11
		expr inside(std::initializer_list<expr> l) { return inside(expr_list(l)); }
#endif

};


} /* namespace pss */

#endif /* INCLUDED_BIT_TYPE_H */

