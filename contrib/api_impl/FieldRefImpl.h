/*
 * FieldRefImpl.h
 *
 *  Created on: May 9, 2016
 *      Author: ballance
 */

#ifndef IMPL_FIELDREFIMPL_H_
#define IMPL_FIELDREFIMPL_H_
#include "api/IField.h"
#include "api/IFieldRef.h"

using namespace psi_api;

namespace psi {

class FieldRefImpl: public IFieldRef {
public:
	FieldRefImpl(const std::vector<IField *> &field_path);

	virtual ~FieldRefImpl();

	virtual ExprType getType() const { return IExpr::ExprType_FieldRef; }

	virtual const std::vector<IField *> &getFieldPath() const { return m_field_path; }

private:
	std::vector<IField *>	m_field_path;

};

} /* namespace psi */

#endif /* IMPL_FIELDREFIMPL_H_ */
