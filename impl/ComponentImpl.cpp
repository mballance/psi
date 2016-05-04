/*
 * ComponentImpl.cpp
 *
 *  Created on: May 3, 2016
 *      Author: ballance
 */

#include "ComponentImpl.h"

namespace psi {

ComponentImpl::ComponentImpl(const std::string &name) : m_name(name) {
	// TODO Auto-generated constructor stub

}

ComponentImpl::~ComponentImpl() {
	// TODO Auto-generated destructor stub
}

const std::string &ComponentImpl::getName() const {
	return m_name;
}

const std::vector<IBaseItem *> &ComponentImpl::getItems() const {
	return m_children;
}

void ComponentImpl::add(IBaseItem *it) {
	m_children.push_back(it);
}


} /* namespace psi */
