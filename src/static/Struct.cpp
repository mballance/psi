/*
 * Struct.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "Struct.h"
#include "TypeRegistry.h"

namespace psi {

Struct::Struct(const std::string &name, IConstructorContext *p) :
		Type((p==nullptr)?TypeRegistry::global():p, name) {

	if (p == nullptr) {
		p = TypeRegistry::global();
	}
	// TODO Auto-generated constructor stub

}

Struct::~Struct() {
	// TODO Auto-generated destructor stub
}

IObjectType::ObjectType Struct::getObjectType() {
	return IObjectType::Struct;
}

Struct Struct::None = Struct("", nullptr);

} /* namespace psi */
