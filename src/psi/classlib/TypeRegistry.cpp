/*
 * TypeRegistry.cpp
 *
 *  Created on: Apr 25, 2016
 *      Author: ballance
 */

#include "classlib/TypeRegistry.h"

#include <stdio.h>

namespace psi {

TypeRegistry::TypeRegistry() : Type(Type::TypeRegistry, nullptr) {
}

TypeRegistry::~TypeRegistry() {
	// TODO Auto-generated destructor stub
}

TypeRegistry *TypeRegistry::global() {
	if (m_global == nullptr) {
		fprintf(stdout, "New\n");
		m_global = new TypeRegistry();
	}
	return m_global;
}

TypeRegistry *TypeRegistry::m_global = 0;

} /* namespace psi */
