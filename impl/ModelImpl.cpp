/*
 * ModelImpl.cpp
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#include "ModelImpl.h"
#include "PackageImpl.h"
#include "ActionImpl.h"

namespace psi {

ModelImpl::ModelImpl() : ScopeItemImpl(IBaseItem::TypeModel), m_global_pkg("") {
	// TODO Auto-generated constructor stub

}

ModelImpl::~ModelImpl() {
	// TODO Auto-generated destructor stub
}

//const std::vector<IPackage*> &ModelImpl::getPackages() {
//	return m_packages;
//}

const std::vector<IBaseItem *> &ModelImpl::getItems() const {
	return m_children;
}

IPackage *ModelImpl::getGlobalPackage() {
	return &m_global_pkg;
}

IPackage *ModelImpl::findPackage(const std::string &name, bool create) {
	std::vector<IBaseItem *>::iterator it;

	for (it=m_children.begin(); it!=m_children.end(); it++) {
//		if ((*it)->getName() == name) {
//			return *it;
//		}
	}

	if (create) {
		return new PackageImpl(name);
	} else {
		return 0;
	}
}

/**
 * Data Types
 */

//IBitType *ModelImpl::mkBitType(uint32_t msb=0, uint32_t lsb=0) {
//	// TODO:
//	return nullptr;
//}
//
//IIntType *ModelImpl::mkIntType(uint32_t msb=31, uint32_t lsb=0) {
//	// TODO:
//	return nullptr;
//}
//
//// TODO: String, Bool types
//
///**
// * Action
// */
//IAction *ModelImpl::mkAction(const std::string &name, IAction *super_type) {
//	return new ActionImpl(name, super_type);
//}

} /* namespace psi */
