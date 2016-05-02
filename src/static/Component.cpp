/*
 * Component.cpp
 *
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#include "Component.h"
#include "TypeRegistry.h"

namespace psi {

Component::Component(const std::string &name, Type *p) :
		Type(Type::TypeComponent, name, (p==nullptr)?TypeRegistry::global():p) { }

Component::~Component() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
