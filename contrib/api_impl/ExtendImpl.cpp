/*
 * ExtendImpl.cpp
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

#include "../api_impl/ExtendImpl.h"

#include "../api_impl/FieldImpl.h"

namespace psi {

ExtendImpl::ExtendImpl(IBaseItem *target) :
		BaseItemImpl(IBaseItem::TypeExtend), m_target(target) {
	switch (target->getType()) {
		case IBaseItem::TypeAction: m_extendType = ExtendType_Action; break;
		case IBaseItem::TypeStruct: m_extendType = ExtendType_Struct; break;
		case IBaseItem::TypeComponent: m_extendType = ExtendType_Component; break;
		default: // error
			m_extendType = ExtendType_Action;
	}
}

ExtendImpl::~ExtendImpl() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
