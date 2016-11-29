/*
 * ExtendImpl.h
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

#ifndef IMPL_EXTENDIMPL_H_
#define IMPL_EXTENDIMPL_H_
#include <vector>
#include "api/IExtend.h"
#include "api/IField.h"
#include "BaseItemImpl.h"
#include "ScopeItemImpl.h"

using namespace psi_api;

namespace psi {

class ExtendImpl:
		public virtual IExtend,
		public virtual BaseItemImpl,
		public virtual ScopeItemImpl {
public:
	ExtendImpl(IBaseItem *target);
	virtual ~ExtendImpl();

	virtual ExtendType getExtendType() const { return m_extendType; }

	virtual IBaseItem *getTarget() const { return m_target; }

private:
	IExtend::ExtendType				m_extendType;
	IBaseItem						*m_target;

};

} /* namespace psi */

#endif /* IMPL_EXTENDIMPL_H_ */
