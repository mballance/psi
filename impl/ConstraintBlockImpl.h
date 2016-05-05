/*
 * ConstraintBlockImpl.h
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#ifndef IMPL_CONSTRAINTBLOCKIMPL_H_
#define IMPL_CONSTRAINTBLOCKIMPL_H_
#include <string>
#include <vector>

#include "api/IConstraintBlock.h"

using namespace psi_api;

namespace psi {

class ConstraintBlockImpl: public IConstraintBlock {
public:
	ConstraintBlockImpl(const std::string &name);

	virtual ~ConstraintBlockImpl();

	virtual ItemType getType() const { return IBaseItem::TypeConstraint; }

	virtual ConstraintType getConstraintType() const { return IConstraint::ConstraintType_Block; }

	virtual const std::string &getName() const { return m_name; }

	virtual void add(IConstraint *c);

	virtual const std::vector<IConstraint *> &getConstraints() const { return m_constraints; }

private:
	std::string								m_name;
	std::vector<IConstraint *>				m_constraints;

};

} /* namespace psi */

#endif /* IMPL_CONSTRAINTBLOCKIMPL_H_ */
