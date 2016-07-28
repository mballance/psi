/*
 * Sequential.cpp
 *
 *  Created on: Jun 20, 2016
 *      Author: ballance
 */

#include "classlib/Sequential.h"

namespace psi {

Sequential::Sequential(const ExprListBuilder &body) : ExprList(body) { }

Sequential::~Sequential() {
	// TODO Auto-generated destructor stub
}

ExprListBuilder Sequential::operator,(const Expr &rhs) {
	return ExprListBuilder(*this, rhs);
}

ExprListBuilder Sequential::operator,(const ExprListBuilder &rhs) {
	return ExprListBuilder(*this, rhs);
}

} /* namespace psi */
