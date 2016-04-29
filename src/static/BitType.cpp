/*
 * BitType.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#include "BitType.h"

namespace psi {

BitType::BitType(
		IConstructorContext		*p,
		const std::string		&name,
		uint32_t				msb,
		uint32_t				lsb) : Type(p, name) {

}

BitType::~BitType() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
