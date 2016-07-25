/*
 * Model.h
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

#ifndef SRC_TYPEREGISTRY_H_
#define SRC_TYPEREGISTRY_H_

#include <string>
#include <vector>

#include "classlib/BaseItem.h"
#include "classlib/TypePath.h"

namespace psi {

class Package;
class Scope;
class Model : public BaseItem {
	friend class Package;

	public:
		Model();

		virtual ~Model();

		static Model *global();

		void push_scope(const Scope *p);

		void pop_scope(const Scope *p);

		const std::vector<const Scope *> &get_scope() const;

		TypePath getActiveTypeName(BaseItem *it);

		TypePath getSuperType(BaseItem *it);

		BaseItem *getActiveScope();

		bool in_field_decl() const { return m_in_field_decl; }

		static TypePath demangle(const Scope *s);

	private:
		std::vector<const Scope *>		m_scope;
		BaseItem						*m_last_scope;
		bool							m_in_field_decl;

		static Model			*m_global;

};


} /* namespace psi */


#endif /* SRC_TYPEREGISTRY_H_ */
