/*
 * BaseItemImpl.h
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

#ifndef IMPL_BASEITEMIMPL_H_
#define IMPL_BASEITEMIMPL_H_
#include "api/IBaseItem.h"

using namespace psi_api;

namespace psi {

	class BaseItemImpl /*: public virtual IBaseItem*/ {
		public:

			BaseItemImpl(IBaseItem::ItemType t);

			virtual ~BaseItemImpl();

			virtual IBaseItem::ItemType getType() const;

		private:
			IBaseItem::ItemType				m_type;
};

} /* namespace psi */

#endif /* IMPL_BASEITEMIMPL_H_ */
