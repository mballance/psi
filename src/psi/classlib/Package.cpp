/*
 * Package.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "classlib/Package.h"

#include <stdio.h>
#include "classlib/TypeRegistry.h"

namespace psi {

Package::Package(const std::string &name, Type *p) :
		Type(Type::TypePackage, name, (p==nullptr)?TypeRegistry::global():p) { }

Package::~Package() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
