/*
 * ExtendImpl.cpp
 *
 *  Created on: May 18, 2016
 *      Author: ballance
 */

#include "ExtendImpl.h"

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

} /* namespace psi */
