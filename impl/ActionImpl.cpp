/*
 * ActionImpl.cpp
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#include "ActionImpl.h"

namespace psi {

ActionImpl::ActionImpl(const std::string &name, IAction *super_type)
	: NamedItemImpl(name, IBaseItem::Action), m_super_type(super_type) {

}

ActionImpl::~ActionImpl() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
