/*
 * StreamStruct.cpp
 *
 *  Created on: Apr 28, 2016
 *      Author: ballance
 */

#include "StreamStruct.h"

namespace psi {

StreamStruct::StreamStruct(
		const std::string 		&name,
		Type 					*p,
		Struct					&super_type) : Struct(Struct::Stream, name, p, super_type) { }

StreamStruct::StreamStruct(
		const std::string 		&name,
		Type 					*p,
		const std::string		&super_type) : Struct(Struct::Stream, name, p, super_type) { }

StreamStruct::~StreamStruct() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
