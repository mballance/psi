/*
 * Component.cpp
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
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#include "ComponentImp.h"
#include "ScopeImp.h"
#include "ModelImp.h"

namespace pss {

Component::Component(const Scope &p) : BaseItem(new ComponentImp(this, p.impl())) {

}

ComponentImp::ComponentImp(Component *master, ScopeImp *p) :
		NamedBaseItemImp(master, BaseItemImp::TypeComponent, p->parent()) {
	setName(ModelImp::global()->getActiveTypeName(master).leaf());
	m_super_type = ModelImp::global()->getSuperType(master);
}

Component::~Component() {
	// TODO Auto-generated destructor stub
}

ComponentImp::~ComponentImp() {
	// TODO Auto-generated destructor stub
}

} /* namespace pss */
