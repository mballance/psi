/*
 * Constraint.h
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef CONSTRAINT_H_
#define CONSTRAINT_H_
#include <string>

#include "Type.h"
#include "ConstraintStmt.h"

namespace psi {

class Constraint : public Type {
public:
	Constraint(Type *p, const ConstraintStmt &stmt);

	Constraint(
			const std::string 		&name,
			Type 					*p,
			const ConstraintStmt 	&stmt);

	virtual ~Constraint();

private:
	const ConstraintStmt			&m_stmt;
};

} /* namespace psi */

#endif /* CONSTRAINT_H_ */
