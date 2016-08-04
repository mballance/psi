/*
 * Scope.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 *  Created on: Jul 7, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_SCOPE_H
#define INCLUDED_SCOPE_H

#include <string>
#include <vector>
#include <typeinfo>

namespace pss {

class BaseItemImp;
class ScopeImp;
class Scope {
public:
	template <class T> Scope(T *t) {
		// Save the type of the super-class
		init(&typeid(T), t);
	}

	template <class T> Scope(T *t, BaseItem *p) {
		// Save the type of the super-class
		init(&typeid(T), p);
	}

	/**
	 * Scope constructor that captures the fact that
	 * this element is a field instance
	 */
	Scope(bool in_field_decl);

	Scope(const char *name);

	Scope(const std::string &name);

	virtual ~Scope();

	ScopeImp *impl() const;

private:

	void init(const std::type_info *type, BaseItem *ctxt);

private:
	ScopeImp				*m_impl;
};

} /* namespace pss */

#endif /* SRC_PSI_CLASSLIB_SCOPE_H_ */
