/*
 * Action.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "Action.h"
#include <stdio.h>

namespace psi {

Action::Action(const std::string &name, IConstructorContext *p) : Struct(name, p) {
	if (p->getObjectType() == Component) {
		p->add(this);
	} else {
		fprintf(stdout, "Note: skipping registering action in scope %s\n",
				IObjectType::toString(p->getObjectType()));
	}
}

Action::~Action() {
	// TODO Auto-generated destructor stub
}

IObjectType::ObjectType Action::getObjectType() {
	return IObjectType::Action;
}

} /* namespace psi */
