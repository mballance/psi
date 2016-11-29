/*
 * ChandleTypeImpl.h
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
 *  Created on: Apr 29, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_CHANDLE_IMPL_H
#define INCLUDED_CHANDLE_IMPL_H
#include "classlib/ChandleType.h"
#include "NamedBaseItemImp.h"
#include "InlineExecUtil.h"

namespace pss {

class ChandleTypeImpl : public NamedBaseItemImp {

	public:

		ChandleTypeImpl(ChandleType *master, BaseItem *p);

		ChandleTypeImpl(ChandleType *master, const std::string &name);

		virtual ~ChandleTypeImpl();

		/**
		 * The get method returns the solve-time value of this
		 * data field. Calling this method is only valid
		 * on fields of this type, and only from within an
		 * inline-exec callback.
		 */
		void *get();

		/**
		 * The set method sets the value of this data field.
		 * Calling this method is only valid on fields
		 * of this type, and only from within an
		 * inline-exec callback.
		 */
		void set(void *v);

	private:
		InlineExecUtil					m_utils;
};

} /* namespace pss */

#endif /* SRC_CLASSLIB_CHANDLE_H_ */
