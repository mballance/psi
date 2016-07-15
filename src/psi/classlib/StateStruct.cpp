/*
 * StateStruct.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#include "classlib/StateStruct.h"
#include "classlib/TypePath.h"

namespace psi {


StateStruct::StateStruct(const Scope &p) :
		Struct(State, p.parent()), initial(this, "initial") {
	TypePath path = Model::global()->getActiveTypeName(this);
	setName(path.leaf());
}

StateStruct::~StateStruct() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
