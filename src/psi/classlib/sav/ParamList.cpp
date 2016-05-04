/*
 * ParamList.cpp
 *
 *  Created on: Apr 29, 2016
 *      Author: ballance
 */

#include "classlib/ParamList.h"

#include "classlib/Expr.h"
#include "classlib/Type.h"

namespace psi {

ParamList::ParamList() {
	// No parameters
}

ParamList::ParamList(const Type &p) {

}

ParamList::ParamList(const Expr &e) {

}

ParamList::ParamList(int v) {

}

ParamList::ParamList(const Param &p1, const Param &p2) {

}

ParamList::~ParamList() {
	// TODO Auto-generated destructor stub
}

ParamList ParamList::operator,(const Param &rhs) {
	return ParamList();
}

ParamList ParamList::operator,(const Type &rhs) {
	return ParamList();
}

} /* namespace psi */
