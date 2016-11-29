/*
 * ActionImpl.cpp
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
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#include "ActionImpl.h"
#include "FieldImpl.h"

namespace psi {

ActionImpl::ActionImpl(
		const std::string 	&name,
		IAction 			*super_type) :
				BaseItemImpl(IBaseItem::TypeAction),
				NamedItemImpl(name), m_super_type(super_type), m_graph(0) {

}

ActionImpl::~ActionImpl() {
	// TODO Auto-generated destructor stub
}

void ActionImpl::setGraph(IGraphStmt *graph) {
	m_graph = graph;
}

IBaseItem *ActionImpl::clone(IItemFactory *f, IAction *action) {
	ActionImpl *ret = new ActionImpl(
			action->getName(),
			action->getSuperType());

	for (std::vector<IBaseItem *>::const_iterator it=action->getItems().begin();
			it!=action->getItems().end(); it++) {
		ret->add(f->clone(*it));
	}

	return ret;
}

} /* namespace psi */
