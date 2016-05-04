/*
 * ModelImpl.cpp
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#include "ModelImpl.h"

#include <stdio.h>
#include <iterator>
#include <string>
#include <vector>

#include "api/IBaseItem.h"
#include "ComponentImpl.h"
#include "ConstraintBlockImpl.h"
#include "LiteralImpl.h"
#include "StructImpl.h"
#include "BinaryExprImpl.h"

namespace psi {

ModelImpl::ModelImpl() : m_global_pkg("") {
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

void ModelImpl::add(IBaseItem *it) {
	m_children.push_back(it);
}

IPackage *ModelImpl::getGlobalPackage() {
	return &m_global_pkg;
}

IPackage *ModelImpl::findPackage(const std::string &name, bool create) {
	std::vector<IBaseItem *>::iterator it;

	for (it=m_children.begin(); it!=m_children.end(); it++) {
		if ((*it)->getType() == IBaseItem::TypePackage) {
			IBaseItem *bi = *it;
			IPackage *pkg_ir = reinterpret_cast<IPackage *>(bi);
			IPackage *pkg_is = static_cast<IPackage *>(bi);
			IPackage *pkg = reinterpret_cast<IPackage *>(*it);
			if (pkg->getName() == name) {
				return pkg;
			}
		}
	}

	if (create) {
		PackageImpl *pkg = new PackageImpl(name);
		m_children.push_back(pkg);
		return pkg;
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

IComponent *ModelImpl::mkComponent(const std::string &name) {
	return new ComponentImpl(name);
}

IStruct *ModelImpl::mkStruct(
		const std::string 		&name,
		IStruct::StructType		t,
		IStruct 				*super_type) {
	return new StructImpl(name, t, super_type);
}

IBinaryExpr *ModelImpl::mkBinExpr(
		IExpr 					*lhs,
		IBinaryExpr::BinOpType	op,
		IExpr 					*rhs) {
	return new BinaryExprImpl(lhs, op, rhs);
}

ILiteral *ModelImpl::mkIntLiteral(int64_t v) {
	return new LiteralImpl(v);
}

ILiteral *ModelImpl::mkBitLiteral(uint64_t v) {
	return new LiteralImpl(v);
}

ILiteral *ModelImpl::mkBoolLiteral(bool v) {
	return new LiteralImpl(v);
}

ILiteral *ModelImpl::mkStringLiteral(const std::string &v) {
	return new LiteralImpl(v);
}

IConstraintBlock *ModelImpl::mkConstraintBlock(const std::string &name) {
	return new ConstraintBlockImpl(name);
}

IConstraintIf *ModelImpl::mkConstraintIf(
		IExpr 			*cond,
		IConstraint 	*true_c,
		IConstraint 	*false_c) {
	return 0;
}

} /* namespace psi */
