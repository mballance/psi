/*
 * IExtend.h
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
 *  Created on: May 18, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IEXTEND_H_
#define SRC_PSI_API_IEXTEND_H_
#include "api/IBaseItem.h"
#include "api/IScopeItem.h"

namespace psi_api {

class IExtend :
		public virtual IBaseItem,
		public virtual IScopeItem {
public:

	enum ExtendType {
		ExtendType_Action,
		ExtendType_Component,
		ExtendType_Struct
	};

	virtual ExtendType getExtendType() const = 0;

	virtual IBaseItem *getTarget() const = 0;


};

}




#endif /* SRC_PSI_API_IEXTEND_H_ */
