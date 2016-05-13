/*
 * ActionImpl.h
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

#ifndef IMPL_ACTIONIMPL_H_
#define IMPL_ACTIONIMPL_H_

#include <string>
#include "api/IAction.h"
#include "NamedItemImpl.h"

using namespace psi_api;

namespace psi {

	class ActionImpl: public IAction {

		public:

			ActionImpl(
					const std::string 	&name,
					IAction 			*super_type);

			virtual ~ActionImpl();

			virtual IAction *getSuperType() const { return m_super_type; }

			virtual IBaseItem::ItemType getType() const {
				return IBaseItem::TypeAction;
			}

			virtual IBaseItem *clone();

			virtual IBaseItem *getParent() const { return m_parent; }

			void setParent(IBaseItem *p) { m_parent = p; }

			virtual const std::string &getName() const;

			virtual const std::vector<IBaseItem *> &getItems() const;

			virtual void add(IBaseItem *);

			virtual IGraphStmt *getGraph() const { return m_graph; }

			virtual void setGraph(IGraphStmt *graph);


		private:
			std::string					m_name;
			IBaseItem					*m_parent;
			IAction						*m_super_type;
			std::vector<IBaseItem *>	m_children;
			IGraphStmt					*m_graph;


};

} /* namespace psi */

#endif /* IMPL_ACTIONIMPL_H_ */
