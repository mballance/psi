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
#include <vector>
#include <typeinfo>
#include "classlib/base_item.h"
#include "classlib/pss_types.h"
#include "classlib/type_decl.h"

namespace pss {

class BaseItemImp;
class ScopeImp;
class scope {
public:
	template <class T> scope(T *t) {
		// Save the type of the super-class
		init(&typeid(T), t,
				type_decl<T>::valid()?type_decl<T>::id():0);
	}

	template <class T> scope(T *t, base_item *p) {
		// Save the type of the super-class
		init(&typeid(T), p,
				type_decl<T>::valid()?type_decl<T>::id():0);
	}

	scope(bool is_type);

	scope(const char *name);

	scope(const std::string &name);

	virtual ~scope();

	ScopeImp *impl() const;

private:

	void init(
			const std::type_info 	*type,
			base_item 				*ctxt,
			base_item				*type_d);

private:
	ScopeImp				*m_impl;
};

} /* namespace pss */

#endif /* SRC_PSI_CLASSLIB_SCOPE_H_ */
