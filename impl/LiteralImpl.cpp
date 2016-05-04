/*
 * LiteralImpl.cpp
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#include "LiteralImpl.h"

namespace psi {

LiteralImpl::LiteralImpl(int64_t v) :
		m_literalType(LiteralInt), m_intval(v) { }

LiteralImpl::LiteralImpl(uint64_t v) :
		m_literalType(LiteralBit), m_intval(v) { }

LiteralImpl::LiteralImpl(bool v) :
		m_literalType(LiteralBool), m_intval(v) { }

LiteralImpl::LiteralImpl(const std::string &s) :
		m_literalType(LiteralString), m_intval(0), m_strval(s) { }

LiteralImpl::~LiteralImpl() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
