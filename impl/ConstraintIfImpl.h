/*
 * ConstraintIfImpl.h
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#ifndef IMPL_CONSTRAINTIFIMPL_H_
#define IMPL_CONSTRAINTIFIMPL_H_
#include "api/IConstraintIf.h"

namespace psi {

class ConstraintIfImpl : public IConstraintIf {
public:
	ConstraintIfImpl(IExpr *cond, IConstraint *true_c, IConstraint *false_c);

	virtual ~ConstraintIfImpl();

	virtual ItemType getType() const { return IBaseItem::TypeConstraint; }

	virtual ConstraintType getConstraintType() const { return IConstraint::ConstraintType_If; }

	virtual IExpr *getCond() const { return m_cond; }

	virtual IConstraint *getTrue() const { return m_true; }

	virtual IConstraint *getFalse() const { return m_false; }

private:

	IExpr					*m_cond;
	IConstraint				*m_true;
	IConstraint				*m_false;

};

} /* namespace psi */

#endif /* IMPL_CONSTRAINTIFIMPL_H_ */
