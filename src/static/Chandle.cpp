/*
 * Chandle.cpp
 *
 *  Created on: Apr 29, 2016
 *      Author: ballance
 */

#include "Chandle.h"

namespace psi {

Chandle::Chandle(const std::string &name, Type *p) : Type(Type::TypeChandle, name, p) { }

Chandle::~Chandle() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
