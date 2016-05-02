/*
 * IntType.cpp
 *
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#include "IntType.h"

namespace psi {

IntType::IntType(
		const std::string 	&name,
		Type 				*p,
		uint32_t			msb,
		uint32_t			lsb) : Type(Type::TypeInt, name, p), m_msb(msb), m_lsb(lsb) {

}

IntType::~IntType() { }

} /* namespace psi */
