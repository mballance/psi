/*
 * Bool.cpp
 *
 *  Created on: Apr 28, 2016
 *      Author: ballance
 */

#include "Bool.h"

namespace psi {

Bool::Bool(const std::string &name, Type *p) : Type(Type::TypeBool, name, p) { }

Bool::~Bool() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
