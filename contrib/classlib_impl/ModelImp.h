/*
 * ModelImp.h
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

#include "BaseItemImp.h"
#include "TypePathImp.h"

namespace pss {

class ModelImp;
class Model : public BaseItem {
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

		TypePathImp getActiveTypeName(BaseItem *it);

		TypePathImp getSuperType(BaseItem *it);

		BaseItem *getActiveScope();

		bool in_field_decl() const { return m_in_field_decl; }

		static TypePathImp demangle(const ScopeImp *s);

		static BaseItem *pOrGlobal(BaseItem *p);

	private:
		std::vector<const ScopeImp *>		m_scope;
		bool								m_in_field_decl;

		static ModelImp					*m_global;

};


} /* namespace pss */


#endif /* SRC_TYPEREGISTRY_H_ */
