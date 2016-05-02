/*
 * String.cpp
 *
 *  Created on: Apr 28, 2016
 *      Author: ballance
 */

#include "String.h"

namespace psi {

String::String(const std::string &name, Type *p) : Type(Type::TypeString, name, p) { }

String::~String() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
