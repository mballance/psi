/*
 * PackageImpl.h
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

#ifndef IMPL_PACKAGEIMPL_H_
#define IMPL_PACKAGEIMPL_H_
#include <vector>

#include "BaseItemImpl.h"
#include "ScopeItemImpl.h"
#include "NamedItemImpl.h"
#include "api/IAction.h"
#include "api/IPackage.h"
#include "api/IStruct.h"

using namespace psi_api;

namespace psi {

class PackageImpl :
		public virtual IPackage,
		public virtual BaseItemImpl,
		public virtual ScopeItemImpl,
		public virtual NamedItemImpl {
	public:

		PackageImpl(const std::string &name, IBaseItem *parent=0);

		virtual ~PackageImpl();

	private:
		std::vector<IAction *>				m_actions;
		std::vector<IStruct *>				m_structs;


};

} /* namespace psi */

#endif /* IMPL_PACKAGEIMPL_H_ */
