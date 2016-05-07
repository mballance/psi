/*
 * ScalarTypeImpl.cpp
 *
 *  Created on: May 6, 2016
 *      Author: ballance
 */

#include "ScalarTypeImpl.h"

namespace psi {

ScalarTypeImpl::ScalarTypeImpl(
		IScalarType::ScalarType			scalar_type,
		uint32_t						msb,
		uint32_t						lsb) : m_scalarType(scalar_type), m_msb(msb), m_lsb(lsb) { }

ScalarTypeImpl::~ScalarTypeImpl() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
