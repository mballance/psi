/*
 * PSIUtil.cpp
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
