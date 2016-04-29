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
		IConstructorContext		*p,
		uint32_t				msb,
		uint32_t				lsb) : Type(p, name) {

}

BitType::~BitType() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
