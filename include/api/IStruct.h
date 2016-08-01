/*
 * IStruct.h
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
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_API_ISTRUCT_H_
#define SRC_API_ISTRUCT_H_
#include <string>
#include <vector>

#include "api/IScopeItem.h"
#include "api/INamedItem.h"

namespace psi_api {

	class IStruct : public IScopeItem, public virtual INamedItem {
	public:

		enum StructType {
			Base,
			Memory,
			State,
			Stream,
			Resource
		};

		public:

			virtual ~IStruct() { }

			virtual IStruct *getSuperType() const = 0;

			virtual const std::string &getName() const = 0;

			virtual const std::vector<IBaseItem *> &getItems() const = 0;

			virtual void add(IBaseItem *it) = 0;

			virtual StructType getStructType() const = 0;

	};
}




#endif /* SRC_API_ISTRUCT_H_ */
