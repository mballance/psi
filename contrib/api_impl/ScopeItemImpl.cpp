/*
 * ScopeItemImpl.cpp
 *
 *  Created on: Aug 15, 2016
 *      Author: ballance
 */

#include "ScopeItemImpl.h"
#include "api/IField.h"

namespace psi {

ScopeItemImpl::ScopeItemImpl() {
	// TODO Auto-generated constructor stub

}

ScopeItemImpl::~ScopeItemImpl() {
	// TODO Auto-generated destructor stub
}

const std::vector<IBaseItem *> &ScopeItemImpl::getItems() const {
	return m_children;
}

void ScopeItemImpl::remove(IBaseItem *it) {
	for (std::vector<IBaseItem *>::iterator i=m_children.begin();
			i!=m_children.end(); i++) {
		if ((*i) == it) {
			m_children.erase(i);
			break;
		}
	}
}

void ScopeItemImpl::add(IBaseItem *item) {
	if (item) {
		item->setParent(dynamic_cast<IBaseItem *>(this));
		m_children.push_back(item);
	}
}

void ScopeItemImpl::insert(std::vector<IBaseItem *>::const_iterator i, IBaseItem *item) {
	item->setParent(dynamic_cast<IBaseItem *>(this));
	m_children.insert(i, item);
}

/**
 * Locates and returns the named field. Returns 0 if
 * the named field does not exist
 */
IField *ScopeItemImpl::getField(const std::string &name) {
	for (std::vector<IBaseItem *>::const_iterator it=m_children.begin();
			it!=m_children.end(); it++) {
		IBaseItem *t = *it;
		if (t->getType() == IBaseItem::TypeField &&
				dynamic_cast<IField *>(t)->getName() == name) {
			return dynamic_cast<IField *>(t);
		}
	}

	return 0;
}


} /* namespace psi */
