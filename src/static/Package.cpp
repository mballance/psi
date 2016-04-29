/*
 * Package.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "Package.h"
#include "TypeRegistry.h"
#include <stdio.h>

namespace psi {

Package::Package(const std::string &name, IConstructorContext *p) {

	if (p == nullptr) {
		p = TypeRegistry::global();
	}

	if (p->getObjectType() == IObjectType::Global) {
		p->add(this);
	} else {
		fprintf(stdout, "Error: Attempting to register package inside wrong scope\n");
	}
}

Package::~Package() {
	// TODO Auto-generated destructor stub
}

IObjectType::ObjectType Package::getObjectType() {
	return IObjectType::Package;
}


} /* namespace psi */
