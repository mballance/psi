/*
 * IBind.h
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
 *  Created on: May 23, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IBIND_H_
#define SRC_PSI_API_IBIND_H_
#include "api/IBaseItem.h"
#include "api/IBindPath.h"

namespace psi_api {

class IBind : public virtual IBaseItem {
public:

	virtual ~IBind() { }

	virtual const std::vector<IBindPath *> &getTargets() const = 0;


};

}




#endif /* SRC_PSI_API_IBIND_H_ */
