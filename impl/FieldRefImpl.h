/*
 * FieldRefImpl.h
 *
 *  Created on: May 9, 2016
 *      Author: ballance
 */

#ifndef IMPL_FIELDREFIMPL_H_
#define IMPL_FIELDREFIMPL_H_
#include "FieldImpl.h"
#include "api/IFieldRef.h"

using namespace psi_api;

namespace psi {

class FieldRefImpl: public IFieldRef {
public:
	FieldRefImpl(FieldImpl *field);

	virtual ~FieldRefImpl();

	virtual ExprType getType() const { return IExpr::ExprType_FieldRef; }

	virtual IField *getField() const { return m_field; }

private:

	FieldImpl				*m_field;
};

} /* namespace psi */

#endif /* IMPL_FIELDREFIMPL_H_ */
