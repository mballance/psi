/*
 * ExtendBase.h
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
 *  Created on: Jul 27, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_EXTEND_BASE_H
#define INCLUDED_EXTEND_BASE_H
#include <stdio.h>
#include "classlib/ExtendItem.h"
#include "classlib/Scope.h"
#include "classlib/BaseItem.h"

namespace pss {

template <class T> class ExtendBase : public T {
protected:

	ExtendBase(const Scope &p) : T(Scope(true)),
		m_item(p, (type_decl<T>::valid())?type_decl<T>::id():this, this) {
	}

private:
	ExtendItem					m_item;

};

}




#endif /* INCLUDE_CLASSLIB_EXTENDBASE_H_ */
