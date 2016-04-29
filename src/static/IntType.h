/*
 * IntType.h
 *
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#ifndef INTTYPE_H_
#define INTTYPE_H_
#include <string>
#include "IConstructorContext.h"
#include "Type.h"

namespace psi {

class IntType : public Type {

	public:
		IntType(const std::string &name, IConstructorContext *p, uint32_t msb, uint32_t lsb);

		virtual ~IntType();
};

} /* namespace psi */

#endif /* INTTYPE_H_ */
