/*
 * NamedScopeItem.cpp
 *
 *  Created on: May 3, 2016
 *      Author: ballance
 */

#include "NamedScopeItemImpl.h"

namespace psi {

NamedScopeItemImpl::NamedScopeItemImpl(IBaseItem::ItemType t, const std::string &name) :
		m_type(t), m_name(name) {
	// TODO Auto-generated constructor stub

}

NamedScopeItemImpl::~NamedScopeItemImpl() {
	// TODO Auto-generated destructor stub
}

void NamedScopeItemImpl::add(IBaseItem *item) {
	m_children.push_back(item);
}

}
