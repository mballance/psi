/*
 * IPackage.h
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
 *  Created on: Apr 25, 2016
 *      Author: ballance
 */

#ifndef SRC_API_IPACKAGE_H_
#define SRC_API_IPACKAGE_H_
#include <string>
#include <vector>

#include "api/IScopeItem.h"
#include "api/INamedItem.h"

namespace psi_api {

class IAction;
class IStruct;

class IPackage : public IScopeItem, public virtual INamedItem {

	public:

		virtual ~IPackage() { }

//		virtual const std::vector<IAction *> &getActions() const = 0;

//		virtual IAction *findAction(const std::string &name) const = 0;

//		virtual void addAction(IAction *action) = 0;

//		virtual const std::vector<IStruct *> getStructs() = 0;
//
//		virtual IStruct *findStruct(const std::string &name) = 0;


};


}




#endif /* SRC_API_IPACKAGE_H_ */
