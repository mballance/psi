/*
 * BitType.h
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef BITTYPE_H_
#define BITTYPE_H_
#include <stdint.h>
#include <string>
#include "IConstructorContext.h"
#include "Type.h"

namespace psi {

class BitType : public Type {

	public:
		BitType(IConstructorContext *p, const std::string &name, uint32_t msb, uint32_t lsb);

		virtual ~BitType();

};


} /* namespace psi */

#endif /* BITTYPE_H_ */
