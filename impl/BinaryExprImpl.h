/*
 * BinaryExprImpl.h
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#ifndef IMPL_BINARYEXPRIMPL_H_
#define IMPL_BINARYEXPRIMPL_H_

#include "api/IBinaryExpr.h"

namespace psi {

class BinaryExprImpl: public IBinaryExpr {
public:
	BinaryExprImpl(
			IExpr					*lhs,
			IBinaryExpr::BinOpType 	op,
			IExpr					*rhs);

	virtual ~BinaryExprImpl();

	virtual ExprType getType() const { return IExpr::ExprType_BinOp; }

	virtual BinOpType getBinOpType() const { return m_op; }

private:

	IExpr									*m_lhs;
	IExpr									*m_rhs;
	IBinaryExpr::BinOpType					m_op;

};

} /* namespace psi */

#endif /* IMPL_BINARYEXPRIMPL_H_ */
