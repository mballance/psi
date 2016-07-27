/*
 * ModelImpl.h
 *
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
 *  Created on: Apr 25, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_MODEL_IMPL_H
#define INCLUDED_MODEL_IMPL_H

#include <string>
#include <vector>

#include "BaseItemImpl.h"
#include "TypePathImpl.h"

namespace psi {

class PackageImpl;
class ScopeImpl;
class ModelImpl : public BaseItemImpl {
	friend class PackageImpl;

	public:
		ModelImpl();

		virtual ~ModelImpl();

		static ModelImpl *global();

		void push_scope(const ScopeImpl *p);

		void pop_scope(const ScopeImpl *p);

		const std::vector<const ScopeImpl *> &get_scope() const;

		TypePathImpl getActiveTypeName(BaseItemImpl *it);

		TypePathImpl getSuperType(BaseItemImpl *it);

		BaseItemImpl *getActiveScope();

		bool in_field_decl() const { return m_in_field_decl; }

		static TypePathImpl demangle(const ScopeImpl *s);

	private:
		std::vector<const ScopeImpl *>		m_scope;
		BaseItemImpl						*m_last_scope;
		bool								m_in_field_decl;

		static ModelImpl					*m_global;

};


} /* namespace psi */


#endif /* SRC_TYPEREGISTRY_H_ */
