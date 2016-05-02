/*
 * BitType.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "BitType.h"

namespace psi {

BitType::BitType(
		const std::string		&name,
		Type					*p,
		uint32_t				msb,
		uint32_t				lsb) : Type(Type::TypeBit, name, p) {

}

BitType::~BitType() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
