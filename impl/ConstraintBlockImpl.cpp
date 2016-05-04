/*
 * ConstraintBlockImpl.cpp
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#include "ConstraintBlockImpl.h"

namespace psi {

ConstraintBlockImpl::ConstraintBlockImpl(const std::string &name) : m_name(name) {
	// TODO Auto-generated constructor stub

}

ConstraintBlockImpl::~ConstraintBlockImpl() {
	// TODO Auto-generated destructor stub
}

void ConstraintBlockImpl::add(IConstraint *c) {
	m_constraints.push_back(c);
}

} /* namespace psi */
