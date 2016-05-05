/*
 * FieldImpl.cpp
 *
 *  Created on: May 5, 2016
 *      Author: ballance
 */

#include "FieldImpl.h"

namespace psi {

FieldImpl::FieldImpl(
		const std::string		&name,
		IBaseItem				*field_type,
		IField::FieldAttr		attr) :
				m_name(name), m_field_type(field_type), m_attr(attr) { }

FieldImpl::~FieldImpl() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
