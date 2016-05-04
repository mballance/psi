/*
 * StructImpl.cpp
 *
 *  Created on: May 3, 2016
 *      Author: ballance
 */

#include "StructImpl.h"

namespace psi {

StructImpl::StructImpl(
		const std::string 		&name,
		IStruct::StructType		t,
		IStruct 				*super_type) :
	m_name(name), m_struct_type(t), m_super_type(super_type) {
	// TODO Auto-generated constructor stub

}

StructImpl::~StructImpl() {
	// TODO Auto-generated destructor stub
}

const std::string &StructImpl::getName() const {
	return m_name;
}

const std::vector<IBaseItem *> &StructImpl::getItems() const {
	return m_children;
}

void StructImpl::add(IBaseItem *it) {
	m_children.push_back(it);
}

} /* namespace psi */
