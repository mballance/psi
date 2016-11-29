/*
 * IStruct.h
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

	class IStruct :
			public virtual IBaseItem,
			public virtual IScopeItem,
			public virtual INamedItem {
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

			virtual StructType getStructType() const = 0;

	};
}




#endif /* SRC_API_ISTRUCT_H_ */
