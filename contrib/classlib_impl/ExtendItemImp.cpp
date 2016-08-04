/*
 * ExtendItem.cpp
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
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#include "ExtendItemImp.h"
#include "ScopeImp.h"

namespace pss {

ExtendItem::ExtendItem(const Scope &p, BaseItem *type_hndl) :
		BaseItem(new ExtendItemImp(this, p.impl()->parent(), BaseItemImp::TypeExtendAction, type_hndl)) {
	// TODO: need to pass through an extension type
}

ExtendItemImp::ExtendItemImp(
		ExtendItem 					*master,
		BaseItem 					*p,
		BaseItemImp::ObjectType 	t,
		BaseItem					*type_hndl) :
		BaseItemImp(master, t, p), m_data_type(toImp(type_hndl)) {

}

void ExtendItemImp::setDataType(BaseItem *t) {
	m_data_type = toImp(t);
}

ExtendItem::~ExtendItem() {
	// TODO Auto-generated destructor stub
}

ExtendItemImp::~ExtendItemImp() {
	// TODO Auto-generated destructor stub
}

} /* namespace pss */
