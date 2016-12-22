/*
 * extend_item.cpp
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
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#include "ExtendItemImp.h"
#include "ScopeImp.h"
#include <stdio.h>

namespace pss {

extend_item::extend_item(
		const scope 		&p,
		base_item 			*type_hndl,
		base_item			*ext_hndl) :
		base_item(new ExtendItemImp(this, p.impl()->parent(), type_hndl, ext_hndl)) {
	// TODO: need to pass through an extension type
	fprintf(stdout, "extend_item::extend_item\n");
}

ExtendItemImp::ExtendItemImp(
		extend_item 					*master,
		base_item 					*p,
		base_item					*type_hndl,
		base_item					*ext_hndl) :
		BaseItemImp(master, BaseItemImp::TypeExtendAction, p), m_data_type(toImp(type_hndl)) {

	// Modify our specific type based on the type we're extending
	switch (type_hndl->impl()->getObjectType()) {
	case BaseItemImp::TypeAction: setObjectType(BaseItemImp::TypeExtendAction); break;
	case BaseItemImp::TypeStruct: setObjectType(BaseItemImp::TypeExtendStruct); break;
	case BaseItemImp::TypeComponent: setObjectType(BaseItemImp::TypeExtendComponent); break;
	}

	m_ext_hndl = ext_hndl->impl();
}

void ExtendItemImp::setDataType(base_item *t) {
	m_data_type = toImp(t);
}

extend_item::~extend_item() {
	// TODO Auto-generated destructor stub
}

ExtendItemImp::~ExtendItemImp() {
	// TODO Auto-generated destructor stub
}

} /* namespace pss */
