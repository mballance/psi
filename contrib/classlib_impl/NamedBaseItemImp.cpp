/*
 * NamedBaseItemImp.cpp
 *
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#include "NamedBaseItemImp.h"
#include "classlib/Action.h"
#include "classlib/Component.h"
#include "classlib/Constraint.h"
#include "classlib/Import.h"
#include "classlib/Field.h"
#include "classlib/Package.h"
#include "classlib/Struct.h"

namespace psi {

NamedBaseItemImp::NamedBaseItemImp(
		BaseItem					*master,
		BaseItemImp::ObjectType 	t,
		BaseItemImp				*p,
		const std::string			&name) : BaseItemImp(master, t, p), m_name(name) {

//	if (p) {
//	fprintf(stdout, "NamedBaseItemImp: \"%s\" p=%s\n", name.c_str(),
//			(!p)?"NULL":(to(p))?to(p)->getName().c_str():"UNNAMED");
//
//	BaseItem *tt = this;
//
//	while (tt) {
//		fprintf(stdout, "  el: %s\n",
//				(to(tt))?to(tt)->getName().c_str():"UNNAMED");
//		tt = tt->getParent();
//	}
//	}
}

NamedBaseItemImp::~NamedBaseItemImp() {
	// TODO Auto-generated destructor stub
}

NamedBaseItemImp *NamedBaseItemImp::to(BaseItemImp *it) {
	switch (it->getObjectType()) {
	case BaseItemImp::TypeAction: return static_cast<Action *>(it);
	case BaseItemImp::TypeComponent: return static_cast<Component *>(it);
	case BaseItemImp::TypeConstraint: return static_cast<Constraint *>(it);
	case BaseItemImp::TypeImport: return static_cast<Import *>(it);
	case BaseItemImp::TypeField: return static_cast<FieldItem *>(it);
	case BaseItemImp::TypePackage: return static_cast<Package *>(it);
	case BaseItemImp::TypeStruct: return static_cast<Struct *>(it);
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

} /* namespace psi */
