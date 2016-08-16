/*
 * ConstraintImpliesImpl.h
 *
 *  Created on: Aug 12, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_CONSTRAINT_IMPLIES_IMPL_H
#define INCLUDED_CONSTRAINT_IMPLIES_IMPL_H
#include "api/IConstraintImplies.h"
#include "BaseItemImpl.h"

using namespace psi_api;

namespace psi {

class ConstraintImpliesImpl:
		public virtual IConstraintImplies,
		public virtual BaseItemImpl {
public:
	ConstraintImpliesImpl(
			IExpr			*cond,
			IConstraint		*imp
			);

	virtual ~ConstraintImpliesImpl();

	virtual ConstraintType getConstraintType() const {
		return IConstraint::ConstraintType_Implies;
	}

	virtual IExpr *getCond() const { return m_cond; }

	virtual IConstraint *getImp() const { return m_imp; }

private:

	IExpr					*m_cond;
	IConstraint				*m_imp;
};

} /* namespace psi */

#endif /* INCLUDED_CONSTRAINT_IMPLIES_IMPL_H */

