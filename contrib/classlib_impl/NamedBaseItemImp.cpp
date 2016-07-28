/*
 * NamedBaseItemImp.cpp
 *
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#include "NamedBaseItemImp.h"
#include "ActionImp.h"
#include "ComponentImp.h"
#include "ConstraintImp.h"
#include "ImportImp.h"
#include "FieldItemImp.h"
#include "PackageImp.h"
#include "StructImp.h"

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
	case BaseItemImp::TypeAction: return static_cast<ActionImp *>(it);
	case BaseItemImp::TypeComponent: return static_cast<ComponentImp *>(it);
	case BaseItemImp::TypeConstraint: return static_cast<ConstraintImp *>(it);
	case BaseItemImp::TypeImport: return static_cast<ImportImp *>(it);
	case BaseItemImp::TypeField: return static_cast<FieldItemImp *>(it);
	case BaseItemImp::TypePackage: return static_cast<PackageImp *>(it);
	case BaseItemImp::TypeStruct: return static_cast<StructImp *>(it);
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
