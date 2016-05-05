/*
 * IntTypeImpl.h
 *
 *  Created on: May 5, 2016
 *      Author: ballance
 */

#ifndef IMPL_INTTYPEIMPL_H_
#define IMPL_INTTYPEIMPL_H_
#include <stdint.h>
#include "api/IIntType.h"

using namespace psi_api;

namespace psi {

class IntTypeImpl: public IIntType {

public:
	IntTypeImpl(uint32_t msb, uint32_t lsb);

	virtual ~IntTypeImpl();

	virtual ItemType getType() const { return IBaseItem::TypeInt; }

	virtual uint32_t getMsb() const { return m_msb; }

	virtual uint32_t getLsb() const { return m_lsb; }

private:

	uint32_t					m_msb;
	uint32_t					m_lsb;

};

} /* namespace psi */

#endif /* IMPL_INTTYPEIMPL_H_ */
