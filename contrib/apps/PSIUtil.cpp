/*
 * PSIUtil.cpp
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
 *  Created on: May 17, 2016
 *      Author: ballance
 */

#include "PSIUtil.h"

namespace psi {
namespace apps {

PSIUtil::PSIUtil() {
	// TODO Auto-generated constructor stub

}

PSIUtil::~PSIUtil() {
	// TODO Auto-generated destructor stub
}

IScopeItem *PSIUtil::toScopeItem(IBaseItem *it) {

	if (it) {
		switch (it->getType()) {
		case IBaseItem::TypeAction: return dynamic_cast<IAction *>(it);
		case IBaseItem::TypeComponent: return dynamic_cast<IComponent *>(it);
		case IBaseItem::TypeModel: return dynamic_cast<IModel *>(it);
		case IBaseItem::TypePackage: return dynamic_cast<IPackage *>(it);
		case IBaseItem::TypeStruct: return dynamic_cast<IStruct *>(it);
		}
	}

	return 0;
}

INamedItem *PSIUtil::toNamedItem(IBaseItem *it) {

	if (it) {
		switch (it->getType()) {
		case IBaseItem::TypeAction: return dynamic_cast<IAction *>(it);
		case IBaseItem::TypeComponent: return dynamic_cast<IComponent *>(it);
		case IBaseItem::TypeField: return dynamic_cast<IField *>(it);
		case IBaseItem::TypePackage: return dynamic_cast<IPackage *>(it);
		case IBaseItem::TypeStruct: return dynamic_cast<IStruct *>(it);
		}
	}

	return 0;
}

}
}
