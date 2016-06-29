/*
 * StateStruct.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#include "StateStruct.h"

namespace psi {

StateStruct::StateStruct(Type *p, const std::string &name, Struct *super) :
		Struct(State, p, name, super), initial(this, "initial") {

}

StateStruct::StateStruct(Type *p) :
		Struct(State, p, "", 0), initial(this, "initial") {

}

StateStruct::~StateStruct() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
