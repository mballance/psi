/*
 * NamedBaseItem.cpp
 *
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#include "classlib/NamedBaseItem.h"
#include "classlib/Action.h"
#include "classlib/Component.h"
#include "classlib/Constraint.h"
#include "classlib/Import.h"
#include "classlib/Field.h"
#include "classlib/Package.h"
#include "classlib/Struct.h"

namespace psi {

NamedBaseItem::NamedBaseItem(
		BaseItem::ObjectType 	t,
		BaseItem 				*p,
		const std::string 		&name) : BaseItem(t, p), m_name(name) {
}

NamedBaseItem::~NamedBaseItem() {
	// TODO Auto-generated destructor stub
}

NamedBaseItem *NamedBaseItem::to(BaseItem *it) {
	switch (it->getObjectType()) {
	case BaseItem::TypeAction: return static_cast<Action *>(it);
	case BaseItem::TypeComponent: return static_cast<Component *>(it);
	case BaseItem::TypeConstraint: return static_cast<Constraint *>(it);
	case BaseItem::TypeImport: return static_cast<Import *>(it);
	case BaseItem::TypeField: return static_cast<FieldItem *>(it);
	case BaseItem::TypePackage: return static_cast<Package *>(it);
	case BaseItem::TypeStruct: return static_cast<Struct *>(it);
	}

	return 0;
}

std::string NamedBaseItem::getName(BaseItem *it) {
	NamedBaseItem *ni = (it)?to(it):0;

	if (ni) {
		return ni->getName();
	} else {
		return "UNNAMED";
	}
}

} /* namespace psi */
