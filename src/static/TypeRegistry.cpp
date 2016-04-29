/*
 * TypeRegistry.cpp
 *
 *  Created on: Apr 25, 2016
 *      Author: ballance
 */

#include "TypeRegistry.h"
#include <stdio.h>

namespace psi {

TypeRegistry::TypeRegistry() {
	// TODO Auto-generated constructor stub
	fprintf(stdout, "TypeRegistry: %p\n", this);

}

TypeRegistry::~TypeRegistry() {
	// TODO Auto-generated destructor stub
}

TypeRegistry *TypeRegistry::global() {
	if (!m_global) {
		m_global = new TypeRegistry();
	}
	return m_global;
}

TypeRegistry *TypeRegistry::m_global = 0;

IObjectType::ObjectType TypeRegistry::getObjectType() {
	return IObjectType::Global;
}

//void TypeRegistry::register_type(TypeFactoryBase *f, ObjectType t) {
//	fprintf(stdout, "%p: register_type - %s %d\n", this, f->get_name().c_str(), t);
//}


TypeFactoryBase::TypeFactoryBase(const std::string &name) {
	m_name = name;
}

TypeFactoryBase::~TypeFactoryBase() {

}

} /* namespace psi */
