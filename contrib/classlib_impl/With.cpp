/*
 * With.cpp
 *
 *  Created on: Jul 15, 2016
 *      Author: ballance
 */

#include "classlib/With.h"
#include "classlib/FieldItem.h"
#include "ExprCore.h"

namespace psi {

With::With(const FieldItem &lhs, const ExprList &stmt) :
	Expr(new ExprCore(Expr::GraphWith, lhs, stmt)) {

}

With::~With() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
