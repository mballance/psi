/*
 * ExtendImpl.cpp
 *
 *  Created on: May 18, 2016
 *      Author: ballance
 */

#include "../api_impl/ExtendImpl.h"

#include "../api_impl/FieldImpl.h"

namespace psi {

ExtendImpl::ExtendImpl(IBaseItem *target) :
		BaseItemImpl(IBaseItem::TypeExtend), m_target(target) {
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

} /* namespace psi */
