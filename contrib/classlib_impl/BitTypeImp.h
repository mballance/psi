/*
 * BitTypeImp.h
 *
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

#ifndef INCLUDED_BIT_TYPE_IMP_H
#define INCLUDED_BIT_TYPE_IMP_H
#include <stdint.h>
#include <string>

#include "../../include/classlib/sav/bit_type.h"
#include "NamedBaseItemImp.h"
#include "api/IField.h"
#include "InlineExecUtil.h"

using namespace psi_api;

namespace pss {

class BitTypeImp : public NamedBaseItemImp {

	public:
		BitTypeImp(
				bit_type				*master,
				base_item 			*p,
				uint32_t			msb,
				uint32_t			lsb);

		BitTypeImp(
				bit_type				*master,
				const std::string	&name,
				uint32_t			msb,
				uint32_t			lsb);

		virtual ~BitTypeImp();

		uint32_t getMsb() const { return m_msb; }

		uint32_t getLsb() const { return m_lsb; }

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

	private:

		uint32_t				m_msb;
		uint32_t				m_lsb;
		std::vector<IField *>	m_field_path;
		InlineExecUtil			m_utils;

};


} /* namespace pss */

#endif /* INCLUDED_BIT_TYPE_IMPL_H */
