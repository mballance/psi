/*
 * ConstraintExpr.h
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#ifndef IMPL_CONSTRAINTEXPRIMPL_H_
#define IMPL_CONSTRAINTEXPRIMPL_H_
#include "api/IConstraintExpr.h"

using namespace psi_api;

namespace psi {

class ConstraintExprImpl: public IConstraintExpr {
public:

	ConstraintExprImpl(IExpr *expr);

	virtual ~ConstraintExprImpl();

	virtual ItemType getType() const { return IBaseItem::TypeConstraint; }

	virtual ConstraintType getConstraintType() const { return IConstraint::ConstraintType_Expr; }

	virtual IExpr *getExpr() const { return m_expr; }

private:

	IExpr					*m_expr;

};

} /* namespace psi */

#endif /* IMPL_CONSTRAINTEXPRIMPL_H_ */
