/*
 * model_impl.h
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

#include "base_item.h"
#include "base_item.h"
#include "type_path.h"

namespace pss {
namespace vendor {

class model_impl;
class base_item;
class scope_impl;

class model_impl : public base_item {
	friend class PackageImpl;

	public:
		model_impl();

		virtual ~model_impl();

		static model_impl *global();

		void push_scope(const scope_impl *p);

		void pop_scope(const scope_impl *p);

		const std::vector<const scope_impl *> &get_scope() const;

		const std::vector<base_item *> &get_scopes() const;

		uint32_t depth() const;

		type_path getActiveTypeName(base_item *it);

		base_item *getActiveType(base_item *it);

		type_path getSuperType();

		base_item *getParentScope();

		bool isField();

		bool isParentField();

		bool isType();

		base_item *getActiveScope();

		const char *get_field_name();

		bool is_field() const;

		static type_path demangle(const scope_impl *s);

		static base_item *pOrGlobal(base_item *p);

		static void print_scopes();

	private:
		std::vector<const scope_impl *>	m_scope;
		std::vector<base_item *>		m_scopes;
		std::string						m_tmpname;

		static model_impl				*m_global;

};


} /* namespace vendor */
} /* namespace pss */


#endif /* SRC_TYPEREGISTRY_H_ */
