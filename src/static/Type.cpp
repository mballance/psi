/*
 * Type.cpp
 *
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#include "Type.h"
#include <stdio.h>

namespace psi {

Type::Type(IConstructorContext *p, const std::string &name) :
		m_name(name), m_parent(p), m_type_data(nullptr) {
	if (getObjectType() == IObjectType::Component &&
			p->getObjectType() == IObjectType::Component) {
		// A component within a component is a field
		p->addField(this);
	} else if (p->getObjectType() == IObjectType::Action ||
		// If the parent is a container, then add this as a field
			IObjectType::isStruct(p->getObjectType())) {
		// Only add as a field if this is a type declaration
		if (!insideInstance()) {
			p->addField(this);
		}
	}
}

Type::Type(const std::string &name, IConstructorContext *p) :
				m_name(name), m_parent(p), m_type_data(nullptr) {
	if (getObjectType() == IObjectType::Component &&
			p->getObjectType() == IObjectType::Component) {
		// A component within a component is a field
		p->addField(this);
	} else if (p->getObjectType() == IObjectType::Action ||
		// If the parent is a container, then add this as a field
			IObjectType::isStruct(p->getObjectType())) {
		// Only add as a field if this is a type declaration
		if (!insideInstance()) {
			p->addField(this);
		}
	}
}

Type::~Type() {
	// TODO Auto-generated destructor stub
}

bool Type::insideInstance() {
	bool ret = false;

	// Traverse up through my hierarchy looking for
	IConstructorContext *c = this;
	IConstructorContext *cp = getParent();

	while (c != nullptr && cp != nullptr) {
		if (c->getObjectType() == IObjectType::Action &&
				cp->getObjectType() == IObjectType::Action) {
			ret = true;
			break;
		}
		c = cp;
		cp = cp->getParent();
	}

	return ret;
}


} /* namespace psi */
