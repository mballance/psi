/*
 * BindImpl.cpp
 *
 *  Created on: May 23, 2016
 *      Author: ballance
 */

#include "../api_impl/BindImpl.h"

namespace psi {

BindImpl::BindImpl(const std::vector<IBindPath *> &targets) :
	m_targets(targets), m_parent(0) {

}

BindImpl::~BindImpl() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
