/*
 * Bind.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#include "Bind.h"

namespace psi {

Bind::Bind(Type *p, Type &i1, Type &i2) : Type(TypeBind, p) {

}

Bind::Bind(Type *p, Type *i1, Type *i2) : Type(TypeBind, p) {

}

Bind::Bind(Type *p, const std::vector<Type *> &items) : Type(TypeBind, p) {
//	std::vector<Type *>::const_iterator it;

}

Bind::~Bind() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
