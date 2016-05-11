/*
 * StateStruct.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#include "StateStruct.h"

namespace psi {

StateStruct::StateStruct(const std::string &name, Type *p) :
		Struct(name, p), initial("initial", this) {

}

StateStruct::~StateStruct() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
