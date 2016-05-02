/*
 * Constraint.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "Constraint.h"

namespace psi {

Constraint::Constraint(Type *p, const ConstraintStmt &stmt) :
		Type(Type::TypeConstraint, p), m_stmt(stmt) { }

Constraint::Constraint(const std::string &name, Type *p, const ConstraintStmt &stmt) :
		Type(Type::TypeConstraint, name, p), m_stmt(stmt) { }

Constraint::~Constraint() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
