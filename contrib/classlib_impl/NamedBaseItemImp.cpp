/*
 * NamedBaseItemImp.cpp
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

#include "NamedBaseItemImp.h"
#include "ActionImp.h"
#include "ComponentImp.h"
#include "ConstraintImp.h"
#include "ImportFuncImp.h"
#include "FieldItemImp.h"
#include "PackageImp.h"
#include "StructImp.h"

namespace pss {

NamedBaseItemImp::NamedBaseItemImp(
		base_item					*master,
		BaseItemImp::ObjectType 	t,
		base_item					*p,
		const std::string			&name) : BaseItemImp(master, t, p), m_name(name) { }

NamedBaseItemImp::~NamedBaseItemImp() {
	// TODO Auto-generated destructor stub
}

NamedBaseItemImp *NamedBaseItemImp::to(BaseItemImp *it) {
	if (it) {
		switch (it->getObjectType()) {
		case BaseItemImp::TypeAction: return static_cast<ActionImp *>(it);
		case BaseItemImp::TypeComponent: return static_cast<ComponentImp *>(it);
		case BaseItemImp::TypeConstraint: return static_cast<ConstraintImp *>(it);
		case BaseItemImp::TypeImport: return static_cast<ImportFuncImp *>(it);
		case BaseItemImp::TypeField: return static_cast<FieldItemImp *>(it);
		case BaseItemImp::TypePackage: return static_cast<PackageImp *>(it);
		case BaseItemImp::TypeStruct: return static_cast<StructImp *>(it);
		}
	}

	return 0;
}

std::string NamedBaseItemImp::getName(BaseItemImp *it) {
	NamedBaseItemImp *ni = (it)?to(it):0;

	if (ni) {
		return ni->getName();
	} else {
		return "UNNAMED";
	}
}

} /* namespace pss */
