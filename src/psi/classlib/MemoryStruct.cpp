/*
 * MemoryStruct.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "classlib/MemoryStruct.h"

#include "classlib/TypeRegistry.h"

namespace psi {

MemoryStruct::MemoryStruct(
		const std::string 		&name,
		Type 					*p,
		Struct					&super_type) :
		Struct(Struct::Memory, name,
				(p==nullptr)?TypeRegistry::global():p, super_type) {
}

MemoryStruct::MemoryStruct(
		const std::string 		&name,
		Type 					*p,
		const std::string		&super_type) :
		Struct(Struct::Memory, name,
				(p==nullptr)?TypeRegistry::global():p, super_type) {
}

MemoryStruct::~MemoryStruct() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
