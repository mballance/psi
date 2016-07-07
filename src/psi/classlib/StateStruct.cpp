/*
 * StateStruct.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#include "StateStruct.h"

namespace psi {

StateStruct::StateStruct(const Parent &p, const std::string &name) :
		Struct(State, p, name), initial(this, "initial") {

}

StateStruct::StateStruct(const Parent &p) :
		Struct(State, p, ""), initial(this, "initial") {

}

StateStruct::~StateStruct() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
