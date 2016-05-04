/*
 * ConstraintIfImpl.cpp
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#include "ConstraintIfImpl.h"

namespace psi {

ConstraintIfImpl::ConstraintIfImpl(IExpr *cond, IConstraint *true_c, IConstraint *false_c) :
	m_cond(cond), m_true(true_c), m_false(false_c) { }

ConstraintIfImpl::~ConstraintIfImpl() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
