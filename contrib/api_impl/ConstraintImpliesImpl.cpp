/*
 * ConstraintImpliesImpl.cpp
 *
 *  Created on: Aug 12, 2016
 *      Author: ballance
 */

#include "ConstraintImpliesImpl.h"

namespace psi {

ConstraintImpliesImpl::ConstraintImpliesImpl(
		IExpr			*cond,
		IConstraint		*imp
		) : BaseItemImpl(IBaseItem::TypeConstraint), m_cond(cond), m_imp(imp) {
	// TODO Auto-generated constructor stub

}

ConstraintImpliesImpl::~ConstraintImpliesImpl() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
