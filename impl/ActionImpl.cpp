/*
 * ActionImpl.cpp
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#include "ActionImpl.h"

namespace psi {

ActionImpl::ActionImpl(const std::string &name, IAction *super_type) :
		m_name(name), m_super_type(super_type) {

}

ActionImpl::~ActionImpl() {
	// TODO Auto-generated destructor stub
}

const std::string &ActionImpl::getName() const {
	return m_name;
}

const std::vector<IBaseItem *> &ActionImpl::getItems() const {
	return m_children;
}

void ActionImpl::add(IBaseItem *it) {
	m_children.push_back(it);
}


} /* namespace psi */
