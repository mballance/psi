/*
 * BitTypeImpl.h
 *
 *  Created on: May 5, 2016
 *      Author: ballance
 */

#ifndef IMPL_BITTYPEIMPL_H_
#define IMPL_BITTYPEIMPL_H_
#include <stdint.h>
#include "api/IBitType.h"

using namespace psi_api;

namespace psi {

class BitTypeImpl: public IBitType {
	public:
		BitTypeImpl(uint32_t msb, uint32_t lsb);

		virtual ~BitTypeImpl();

		virtual ItemType getType() const { return IBaseItem::TypeBit; }

		virtual uint32_t getMsb() const { return m_msb; }

		virtual uint32_t getLsb() const { return m_lsb; }

	private:

		uint32_t			m_msb;
		uint32_t			m_lsb;
};

} /* namespace psi */

#endif /* IMPL_BITTYPEIMPL_H_ */
