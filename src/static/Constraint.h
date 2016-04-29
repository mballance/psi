/*
 * Constraint.h
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef CONSTRAINT_H_
#define CONSTRAINT_H_
#include <string>
#include "IConstructorContext.h"
#include "ConstraintStmt.h"

namespace psi {

class Constraint {
public:
	Constraint(IConstructorContext *p, const ConstraintStmt &stmt);

	Constraint(const std::string &name, IConstructorContext *p, const ConstraintStmt &stmt);

	virtual ~Constraint();
};

} /* namespace psi */

#endif /* CONSTRAINT_H_ */
