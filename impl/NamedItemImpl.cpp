/*
 * NamedItemImpl.cpp
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#include "NamedItemImpl.h"

namespace psi {

NamedItemImpl::NamedItemImpl(const std::string &name, IBaseItem::ItemType t) :
	BaseItemImpl(t), m_name(name) {

}

NamedItemImpl::~NamedItemImpl() {
	// TODO Auto-generated destructor stub
}

const std::string &NamedItemImpl::getName() {
	return m_name;
}

} /* namespace psi */
