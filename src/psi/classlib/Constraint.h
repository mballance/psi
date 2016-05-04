/*
 * Constraint.h
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef CONSTRAINT_H_
#define CONSTRAINT_H_
#include <string>

#include "classlib/ConstraintStmt.h"
#include "classlib/Type.h"

namespace psi {

class Constraint : public Type {
public:
	Constraint(Type *p, const ExprList &stmt);

	Constraint(
			const std::string 		&name,
			Type 					*p,
			const ExprList 			&stmt);

	virtual ~Constraint();

	ExprList &getStmt() {
		return m_stmt;
	}

private:
	ExprList				m_stmt;
};

} /* namespace psi */

#endif /* CONSTRAINT_H_ */
