/*
 * pool.h
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
 *  Created on: Apr 28, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_POOL_H
#define INCLUDED_POOL_H
#include "classlib/FieldItem.h"
#include "classlib/type_decl.h"

namespace pss {

template <class T> class pool : public T {

	public:
		pool(const Scope &name) : T(static_cast<T *>(this)) {
			FieldItem &it = static_cast<FieldItem &>(*this);
			it.setModifiers(FieldItem::AttrPool);
		}

		virtual ~pool() { }

};

} /* namespace pss */

#endif /* INCLUDED_POOL_H */
