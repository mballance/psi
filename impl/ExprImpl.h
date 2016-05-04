/*
 * ExprImpl.h
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#ifndef IMPL_EXPRIMPL_H_
#define IMPL_EXPRIMPL_H_

namespace psi {

class ExprImpl: public IExpr {
public:

	ExprImpl(IExpr::ExprType t);

	virtual ~ExprImpl();

	virtual ExprType getType() const { return m_type; }

private:

	IExpr::ExprType				m_type;

};

} /* namespace psi */

#endif /* IMPL_EXPRIMPL_H_ */
