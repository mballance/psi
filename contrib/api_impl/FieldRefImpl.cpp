/*
 * FieldRefImpl.cpp
 *
 *  Created on: May 9, 2016
 *      Author: ballance
 */

#include "../api_impl/FieldRefImpl.h"

namespace psi {

FieldRefImpl::FieldRefImpl(const std::vector<IField *> &field_path) :
		m_field_path(field_path) {
	// TODO Auto-generated constructor stub

}

FieldRefImpl::FieldRefImpl(IField *field_path) {
	m_field_path.push_back(field_path);
}

FieldRefImpl::~FieldRefImpl() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
