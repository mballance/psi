/*
 * NamedBaseItemImpl.cpp
 *
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#include "NamedBaseItemImpl.h"
#include "classlib/Action.h"
#include "classlib/Component.h"
#include "classlib/Constraint.h"
#include "classlib/Import.h"
#include "classlib/Field.h"
#include "classlib/Package.h"
#include "classlib/Struct.h"

namespace psi {

NamedBaseItemImpl::NamedBaseItemImpl(
		BaseItem					*master,
		BaseItemImpl::ObjectType 	t,
		BaseItemImpl				*p,
		const std::string			&name) : BaseItemImpl(master, t, p), m_name(name) {

//	if (p) {
//	fprintf(stdout, "NamedBaseItemImpl: \"%s\" p=%s\n", name.c_str(),
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

NamedBaseItemImpl::~NamedBaseItemImpl() {
	// TODO Auto-generated destructor stub
}

NamedBaseItemImpl *NamedBaseItemImpl::to(BaseItemImpl *it) {
	switch (it->getObjectType()) {
	case BaseItemImpl::TypeAction: return static_cast<Action *>(it);
	case BaseItemImpl::TypeComponent: return static_cast<Component *>(it);
	case BaseItemImpl::TypeConstraint: return static_cast<Constraint *>(it);
	case BaseItemImpl::TypeImport: return static_cast<Import *>(it);
	case BaseItemImpl::TypeField: return static_cast<FieldItem *>(it);
	case BaseItemImpl::TypePackage: return static_cast<Package *>(it);
	case BaseItemImpl::TypeStruct: return static_cast<Struct *>(it);
	}

	return 0;
}

std::string NamedBaseItemImpl::getName(BaseItemImpl *it) {
	NamedBaseItemImpl *ni = (it)?to(it):0;

	if (ni) {
		return ni->getName();
	} else {
		return "UNNAMED";
	}
}

} /* namespace psi */
