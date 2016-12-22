/*
 * extend_base.h
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
#include "classlib/extend_item.h"
#include "classlib/scope.h"
#include "classlib/base_item.h"

namespace pss {

template <class T> class extend_base : public T {
protected:

	extend_base(const scope &p) : T(scope(true)),
		m_item(p, (type_decl<T>::valid())?type_decl<T>::id():this, this) {
	}

private:
	extend_item					m_item;

};

}




#endif /* INCLUDE_CLASSLIB_EXTENDBASE_H_ */
