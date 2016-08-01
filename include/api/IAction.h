/*
 * IAction.h
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
#ifndef SRC_API_IACTION_H_
#define SRC_API_IACTION_H_
#include <string>
#include <vector>

#include "api/IBaseItem.h"
#include "api/IScopeItem.h"
#include "api/IGraphStmt.h"
#include "api/INamedItem.h"

namespace psi_api {
	/**
	 * Specifies the API to an Action declaration
	 */
	class IAction : public IScopeItem, public virtual INamedItem {

		public:

			virtual ~IAction() { };

			virtual IAction *getSuperType() const = 0;

			/**
			 * Returns the name of the action
			 */
			virtual const std::string &getName() const = 0;

			/**
			 * Returns a list of the sub-elements of the action.
			 */
			virtual const std::vector<IBaseItem *> &getItems() const = 0;

			/**
			 * Adds a new sub-element to the action declaration
			 */
			virtual void add(IBaseItem *it) = 0;

			/**
			 * Returns the graph body, or null if there is none
			 */
			virtual IGraphStmt *getGraph() const = 0;

			/**
			 * Sets the graph body
			 */
			virtual void setGraph(IGraphStmt *graph) = 0;

	};
}




#endif /* SRC_API_IACTION_H_ */
