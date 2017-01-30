/*
 * ActionImpl.h
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

#ifndef IMPL_ACTIONIMPL_H_
#define IMPL_ACTIONIMPL_H_

#include <string>

#include "BaseItemImpl.h"
#include "NamedItemImpl.h"
#include "ScopeItemImpl.h"
#include "api/IAction.h"
#include "api/IField.h"
#include "api/IItemFactory.h"

using namespace psi_api;

namespace psi {

	class ActionImpl:
		public virtual IAction,
		public virtual BaseItemImpl,
		public virtual NamedItemImpl,
		public virtual ScopeItemImpl {

		public:

			ActionImpl(
					const std::string 	&name,
					IAction 			*super_type);

			virtual ~ActionImpl();

			virtual IAction *getSuperType() const { return m_super_type; }

			virtual IGraphStmt *getGraph() const { return m_graph; }

			virtual void setGraph(IGraphStmt *activity);

			static IBaseItem *clone(IItemFactory *f, IAction *action);


		private:
			IAction						*m_super_type;
			IGraphStmt					*m_graph;

};

} /* namespace psi */

#endif /* IMPL_ACTIONIMPL_H_ */
