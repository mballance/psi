/*
 * IComponent.h
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
 *  Created on: May 3, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_ICOMPONENT_H_
#define SRC_PSI_API_ICOMPONENT_H_
#include <string>
#include <vector>

#include "api/IScopeItem.h"
#include "api/INamedItem.h"

namespace psi_api {

class IComponent:
		public virtual IBaseItem,
		public virtual IScopeItem,
		public virtual INamedItem {
	public:

		virtual ~IComponent() { };

};

} /* namespace psi */

#endif /* SRC_PSI_API_ICOMPONENT_H_ */
