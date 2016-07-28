/*
 * ExprImportCall.cpp
 *
 *  Created on: May 11, 2016
 *      Author: ballance
 */

#include "classlib/ExprImportCall.h"
#include "classlib/Import.h"
#include "ExprCore.h"

namespace psi {

ExprImportCall::ExprImportCall(Import &import, const ExprList &plist) :
	Expr(new ExprCore(import, plist)) { }

ExprImportCall::~ExprImportCall() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
