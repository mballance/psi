/*
 * ExprImportCall.h
 *
 *  Created on: May 11, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_CLASSLIB_EXPRIMPORTCALL_H_
#define SRC_PSI_CLASSLIB_EXPRIMPORTCALL_H_

#include "Expr.h"

namespace psi {

class Import;
class ExprList;
class ExprImportCall: public Expr {
public:
	ExprImportCall(Import &import, const ExprList &plist);

	virtual ~ExprImportCall();

//	ExprList operator,(const Expr &rhs);

};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_EXPRIMPORTCALL_H_ */
