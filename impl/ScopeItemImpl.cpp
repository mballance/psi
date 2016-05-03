/*
 * ScopeItemImpl.cpp
 *
 *  Created on: May 2, 2016
 *      Author: ballance
 */

#include "ScopeItemImpl.h"

namespace psi {

ScopeItemImpl::ScopeItemImpl(IBaseItem::ItemType t) : BaseItemImpl(t) {
	// TODO Auto-generated constructor stub

}

ScopeItemImpl::~ScopeItemImpl() {
	// TODO Auto-generated destructor stub
}

const std::vector<IBaseItem *> &ScopeItemImpl::getItems() const {
	return m_children;
}

void ScopeItemImpl::add(IBaseItem *item) {
	m_children.push_back(item);
}

} /* namespace psi */
