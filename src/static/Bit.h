/*
 * Bit.h
 *
 *  Created on: Apr 25, 2016
 *      Author: ballance
 */

#ifndef SRC_BIT_H_
#define SRC_BIT_H_
#include "Types.h"
#include "BitType.h"

namespace psi {

template <uint32_t MSB=0, uint32_t LSB=0> class Bit : public BitType {
	public:
		Bit(IConstructorContext *p, const std::string &name) :
			BitType(p, name, MSB, LSB) {
		}

		virtual ~Bit() { }
};

} /* namespace psi */

#endif /* SRC_BIT_H_ */
