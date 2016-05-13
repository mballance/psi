/*
 * PackageImpl.h
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
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef IMPL_PACKAGEIMPL_H_
#define IMPL_PACKAGEIMPL_H_
#include <vector>
#include "api/IAction.h"
#include "api/IPackage.h"
#include "api/IStruct.h"
#include "NamedScopeItemImpl.h"
#include "BaseItemImpl.h"

using namespace psi_api;

namespace psi {

class PackageImpl : public IPackage  {
	public:

		PackageImpl(const std::string &name, IBaseItem *parent=0);

		virtual ~PackageImpl();

		virtual IBaseItem::ItemType getType() const { return IBaseItem::TypePackage; }

		virtual IBaseItem *clone();

		virtual IBaseItem *getParent() const { return m_parent; }

		void setParent(IBaseItem *p) { m_parent = p; }

		virtual const std::vector<IBaseItem *> &getItems() const {
			return m_children;
		}

		virtual void add(IBaseItem *item);

		virtual const std::string &getName() const {
			return m_name;
		}

		// TODO: Move to Component
		virtual const std::vector<IAction *> getActions();

		virtual IAction *findAction(const std::string &name);

		virtual void addAction(IAction *action);

		virtual const std::vector<IStruct *> getStructs();

		virtual IStruct *findStruct(const std::string &name);

	private:
		IBaseItem							*m_parent;
		std::string							m_name;
		std::vector<IBaseItem *>			m_children;
		std::vector<IAction *>				m_actions;
		std::vector<IStruct *>				m_structs;


};

} /* namespace psi */

#endif /* IMPL_PACKAGEIMPL_H_ */
