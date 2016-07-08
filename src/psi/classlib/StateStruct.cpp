/*
 * StateStruct.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#include "StateStruct.h"

namespace psi {


StateStruct::StateStruct(const Scope &p) :
		Struct(State, p.parent()), initial(this, "initial") {

}

StateStruct::~StateStruct() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
