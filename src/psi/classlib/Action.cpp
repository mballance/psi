/*
 * Action.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "classlib/Action.h"

#include <stdio.h>
#include "classlib/TypeRegistry.h"

namespace psi {

Action::Action(const std::string &name, Type *p) : Type(Type::TypeAction, name, p) { }

Action::~Action() {
	// TODO Auto-generated destructor stub
}


} /* namespace psi */
