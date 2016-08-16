/*
 * BindImpl.cpp
 *
 *  Created on: May 23, 2016
 *      Author: ballance
 */

#include "BindImpl.h"

namespace psi {

BindImpl::BindImpl(const std::vector<IBindPath *> &targets) :
		BaseItemImpl(IBaseItem::TypeBind), m_targets(targets) {

}

BindImpl::~BindImpl() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
