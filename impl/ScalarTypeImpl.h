/*
 * ScalarTypeImpl.h
 *
 *  Created on: May 6, 2016
 *      Author: ballance
 */

#ifndef IMPL_SCALARTYPEIMPL_H_
#define IMPL_SCALARTYPEIMPL_H_
#include "api/IScalarType.h"

namespace psi {

class ScalarTypeImpl: public psi_api::IScalarType {
public:
	ScalarTypeImpl(
			IScalarType::ScalarType			scalar_type,
			uint32_t						msb,
			uint32_t						lsb);

	virtual ~ScalarTypeImpl();

	virtual ItemType getType() const { return IBaseItem::TypeScalar; }

	virtual ScalarType getScalarType() const { return m_scalarType; }

	/**
	 * Returns the MSB of the type for Bit and Int types
	 */
	virtual uint32_t getMSB() const { return m_msb; }

	/**
	 * Returns the LSB of the type for Bit and Int types
	 */
	virtual uint32_t getLSB() const { return m_lsb; }


private:
	IScalarType::ScalarType			m_scalarType;
	uint32_t						m_msb;
	uint32_t						m_lsb;
};

} /* namespace psi */

#endif /* IMPL_SCALARTYPEIMPL_H_ */
