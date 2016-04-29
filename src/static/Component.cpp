/*
 * Component.cpp
 *
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#include "Component.h"
#include "TypeRegistry.h"

namespace psi {

Component::Component(const std::string &name, IConstructorContext *p) :
		Type((p==nullptr)?TypeRegistry::global():p, name) {

	if (p == nullptr) {
		p = TypeRegistry::global();
	}

	if (p->getObjectType() == IObjectType::Global) {
		// Register ourselves as type
		p->add(this);
	}
}

Component::~Component() {
	// TODO Auto-generated destructor stub
}

IConstructorContext::ConstructorContextType Component::getContextType() {
	return ConstructorContext_TypeElab;
}

IObjectType::ObjectType Component::getObjectType() {
	return IObjectType::Component;
}

} /* namespace psi */
