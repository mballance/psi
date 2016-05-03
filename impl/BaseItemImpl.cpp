/*
 * BaseItemImpl.cpp
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#include "BaseItemImpl.h"

namespace psi {

BaseItemImpl::BaseItemImpl(IBaseItem::ItemType t) : m_type(t) {
	// TODO Auto-generated constructor stub

}

BaseItemImpl::~BaseItemImpl() {
	// TODO Auto-generated destructor stub
}

IBaseItem::ItemType BaseItemImpl::getType() {
	return m_type;
}

} /* namespace psi */
