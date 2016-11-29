/*
 * Lock.h
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
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef LOCK_H_
#define LOCK_H_
#include <string>

#include "classlib/FieldBase.h"
#include "classlib/TypeDecl.h"

namespace pss {

template <class T> class Lock: public FieldBase<T> {

	public:
		Lock(BaseItem *p, const std::string &name) :
			FieldBase<T>(FieldItem::AttrLock, p, name) { }

		virtual ~Lock() { }
};

} /* namespace pss */

#endif /* LOCK_H_ */
