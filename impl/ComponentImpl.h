/*
 * ComponentImpl.h
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
 *  Created on: May 3, 2016
 *      Author: ballance
 */

#ifndef IMPL_COMPONENTIMPL_H_
#define IMPL_COMPONENTIMPL_H_
#include "api/IComponent.h"

using namespace psi_api;

namespace psi {

class ComponentImpl: public IComponent {

public:
	ComponentImpl(const std::string &name);

	virtual ~ComponentImpl();

	virtual IBaseItem::ItemType getType() const {
		return IBaseItem::TypeComponent;
	}

	virtual const std::string &getName() const;

	virtual IBaseItem *clone();

	virtual IBaseItem *getParent() const { return m_parent; }

	void setParent(IBaseItem *p) { m_parent = p; }

	virtual const std::vector<IBaseItem *> &getItems() const;

	virtual void add(IBaseItem *it);


private:
	IBaseItem					*m_parent;
	std::string					m_name;
	std::vector<IBaseItem *>	m_children;

};

} /* namespace psi */

#endif /* IMPL_COMPONENTIMPL_H_ */
