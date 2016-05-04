/*
 * IntType.h
 *
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#ifndef INTTYPE_H_
#define INTTYPE_H_
#include <string>

#include "classlib/Type.h"

namespace psi {

class IntType : public Type {

	public:
		IntType(
				const std::string 	&name,
				Type 				*p,
				uint32_t			msb,
				uint32_t			lsb);

		virtual ~IntType();

	private:

		uint32_t					m_msb;
		uint32_t					m_lsb;
};

} /* namespace psi */

#endif /* INTTYPE_H_ */
