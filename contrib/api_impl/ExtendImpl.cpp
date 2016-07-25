/*
 * ExtendImpl.cpp
 *
 *  Created on: May 18, 2016
 *      Author: ballance
 */

#include "../api_impl/ExtendImpl.h"

#include "../api_impl/FieldImpl.h"

namespace psi {

ExtendImpl::ExtendImpl(IBaseItem *target) : m_target(target),
		m_parent(0) {
	switch (target->getType()) {
		case IBaseItem::TypeAction: m_extendType = ExtendType_Action; break;
		case IBaseItem::TypeStruct: m_extendType = ExtendType_Struct; break;
		case IBaseItem::TypeComponent: m_extendType = ExtendType_Component; break;
		default: // error
			m_extendType = ExtendType_Action;
	}
}

ExtendImpl::~ExtendImpl() {
	// TODO Auto-generated destructor stub
}

void ExtendImpl::add(IBaseItem *it) {
	m_items.push_back(it);
	it->setParent(this);
}

/**
 * Locates and returns the named field. Returns 0 if
 * the named field does not exist
 */
IField *ExtendImpl::getField(const std::string &name) {
	IField *ret = 0;
	std::vector<IBaseItem *>::const_iterator it;

	for (it=m_items.begin(); it!=m_items.end(); it++) {
		if ((*it)->getType() == IBaseItem::TypeField &&
				static_cast<FieldImpl *>(*it)->getName() == name) {
			ret = static_cast<FieldImpl *>(*it);
			break;
		}

	}

	return ret;
}

} /* namespace psi */
