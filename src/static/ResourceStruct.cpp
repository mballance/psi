/*
 * ResourceStruct.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "ResourceStruct.h"
#include "TypeRegistry.h"

namespace psi {

ResourceStruct::ResourceStruct(const std::string &name, IConstructorContext *p) :
	Struct(name, (p==nullptr)?TypeRegistry::global():p), instance_id(this, "instance_id") {

	if (p == nullptr) {
		p = TypeRegistry::global();
	}

}

ResourceStruct::~ResourceStruct() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
