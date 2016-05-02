/*
 * ResourceStruct.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "ResourceStruct.h"
#include "TypeRegistry.h"

namespace psi {

ResourceStruct::ResourceStruct(
		const std::string 	&name,
		Type 				*p,
		Struct				&super_type) :
				Struct(Struct::Resource, name, p, super_type),
				instance_id("instance_id", this) { }

ResourceStruct::ResourceStruct(
		const std::string 	&name,
		Type 				*p,
		const std::string	&super_type) :
				Struct(Struct::Resource, name, p, super_type),
				instance_id("instance_id", this) { }

ResourceStruct::~ResourceStruct() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
