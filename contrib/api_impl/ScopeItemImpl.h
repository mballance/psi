/*
 * ScopeItemImpl.h
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
 *  Created on: Aug 15, 2016
 *      Author: ballance
 */

#ifndef CONTRIB_API_IMPL_SCOPEITEMIMPL_H_
#define CONTRIB_API_IMPL_SCOPEITEMIMPL_H_
#include "api/IScopeItem.h"

using namespace psi_api;

namespace psi {

class ScopeItemImpl : public virtual IScopeItem {
public:
	ScopeItemImpl();

	virtual ~ScopeItemImpl();

	virtual const std::vector<IBaseItem *> &getItems() const;

	virtual void remove(IBaseItem *it);

	virtual void add(IBaseItem *item);

	void insert(std::vector<IBaseItem *>::iterator i, IBaseItem *item);

	/**
	 * Locates and returns the named field. Returns 0 if
	 * the named field does not exist
	 */
	virtual IField *getField(const std::string &name);

private:
	std::vector<IBaseItem *>				m_children;

};

} /* namespace psi */

#endif /* CONTRIB_API_IMPL_SCOPEITEMIMPL_H_ */
