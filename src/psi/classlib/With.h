/*
 * With.h
 *
 *  Created on: Jul 15, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_CLASSLIB_WITH_H_
#define SRC_PSI_CLASSLIB_WITH_H_

#include "classlib/Expr.h"

namespace psi {

class FieldItem;
class ExprList;
class With: public Expr {
public:
	With(const FieldItem &lhs, const ExprList &stmt);

	virtual ~With();
};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_WITH_H_ */
