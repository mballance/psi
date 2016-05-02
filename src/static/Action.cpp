/*
 * Action.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "Action.h"
#include "TypeRegistry.h"
#include <stdio.h>

namespace psi {

Action::Action(const std::string &name, Type *p) : Type(Type::TypeAction, name, p) { }

Action::~Action() {
	// TODO Auto-generated destructor stub
}


} /* namespace psi */
