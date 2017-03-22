/*
 * ModelImp.h
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
 *  Created on: Apr 25, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_MODEL_IMPL_H
#define INCLUDED_MODEL_IMPL_H

#include <string>
#include <vector>

#include "BaseItemImp.h"
#include "TypePathImp.h"

namespace pss {

class ModelImp;
class Model : public base_item {
public:

	Model(ModelImp *imp);

};

class PackageImpl;
class ScopeImp;
class ModelImp : public BaseItemImp {
	friend class PackageImpl;

	public:
		ModelImp();

		virtual ~ModelImp();

		static ModelImp *global();

		void push_scope(const ScopeImp *p);

		void pop_scope(const ScopeImp *p);

		const std::vector<const ScopeImp *> &get_scope() const;

		const std::vector<base_item *> &get_scopes() const;

		uint32_t depth() const;

		TypePathImp getActiveTypeName(base_item *it);

		BaseItemImp *getActiveType(base_item *it);

		TypePathImp getSuperType();

		base_item *getParentScope();

		bool isField();

		bool isParentField();

		bool isType();

		base_item *getActiveScope();

		const char *get_field_name();

		bool is_field() const;

		static TypePathImp demangle(const ScopeImp *s);

		static base_item *pOrGlobal(base_item *p);

		static void print_scopes();

	private:
		std::vector<const ScopeImp *>		m_scope;
		std::vector<base_item *>				m_scopes;
		std::string							m_tmpname;

		static ModelImp					*m_global;

};


} /* namespace pss */


#endif /* SRC_TYPEREGISTRY_H_ */
