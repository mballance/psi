/*
 * StateStruct.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#include "StateStructImp.h"

#include "NamedBaseItemImp.h"
#include "ModelImp.h"
#include "ScopeImp.h"

namespace psi {

StateStruct::StateStruct(const Scope &p) :
		Struct(new StateStructImp(this, p.impl())), initial(this, "initial") {
}

StateStructImp::StateStructImp(StateStruct *master, ScopeImp *p) :
		StructImp(master, p, StructImp::State) {
	TypePathImp path = ModelImp::global()->getActiveTypeName(this);
	setName(path.leaf());

	// TODO: mark 'initial' as an internal field
//	initial.setInternal(true);
}

StateStruct::~StateStruct() {
	// TODO Auto-generated destructor stub
}

StateStructImp::~StateStructImp() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
