/*
 * IObjectType.cpp
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */
#include "IObjectType.h"

namespace psi {

const char *IObjectType::toString(ObjectType t) {

	switch (t) {
		case IObjectType::Action: return "Action";
		case IObjectType::Component: return "Component";
		case IObjectType::Global: return "Global";
		case IObjectType::MemoryStruct: return "MemoryStruct";
		case IObjectType::Package: return "Package";
		case IObjectType::Struct: return "Struct";
		case IObjectType::Type: return "Type";
		default: return "UNKNOWN";
	}
}

bool IObjectType::isStruct(ObjectType t) {
	return (t == IObjectType::Struct ||
			t == IObjectType::MemoryStruct ||
			t == IObjectType::ResourceStruct ||
			t == IObjectType::StreamStruct);
}


}


