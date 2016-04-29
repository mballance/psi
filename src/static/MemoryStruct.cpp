/*
 * MemoryStruct.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "MemoryStruct.h"
#include "TypeRegistry.h"

namespace psi {

MemoryStruct::MemoryStruct(
		const std::string 		&name,
		IConstructorContext 	*p,
		Struct					&super_type) :
		Struct(name, (p==nullptr)?TypeRegistry::global():p) {

	if (p == nullptr) {
		p = TypeRegistry::global();
	}
}

MemoryStruct::MemoryStruct(
		const std::string 		&name,
		IConstructorContext 	*p,
		const std::string		&super_type) :
		Struct(name, (p==nullptr)?TypeRegistry::global():p) {

	if (p == nullptr) {
		p = TypeRegistry::global();
	}
}

MemoryStruct::~MemoryStruct() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
