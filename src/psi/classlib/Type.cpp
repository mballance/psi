/*
 * Type.cpp
 *
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#include "classlib/Type.h"

#include <stdio.h>
#include "classlib/ExprCore.h"

namespace psi {

Type::Type(Type::ObjectType t, Type *p) :
		m_type(t), m_name(""), m_parent(p),
		m_type_data(nullptr), m_isRand(false),
		m_isInput(false), m_isOutput(false) {
	m_type_data = nullptr;

	if (p != nullptr) {
		p->add(this);
	}
}

Type::Type(Type::ObjectType t, const std::string &name, Type *p) :
		m_type(t), m_name(name), m_parent(p),
		m_type_data(nullptr), m_isRand(false),
		m_isInput(false), m_isOutput(false) {
	m_type_data = nullptr;

	if (p != nullptr) {
		p->add(this);
	}
}

Type::~Type() {
	// TODO Auto-generated destructor stub
}

Expr Type::operator [] (const Expr &rhs) {
	return Expr(new ExprCore(Expr::BinOp_ArrayRef, *this, rhs));
}

ExprList Type::operator,(const Type &rhs) {
	return ExprList(Expr(*this), Expr(rhs));
}

void Type::add(Type *item) {
	m_children.push_back(item);
}

void Type::setObjectType(Type::ObjectType t) {
	m_type = t;
}

const std::vector<Type *> &Type::getChildren() const {
	return m_children;
}

const char *Type::toString(ObjectType t) {
	switch (t) {
		case TypeAction: return "TypeAction";
		case TypeBit: return "TypeBit";
		case TypeBool: return "TypeBool";
		case TypeChandle: return "TypeChandle";
		case TypeComponent: return "TypeComponent";
		case TypeConstraint: return "TypeConstraint";
		case TypeImport: return "TypeImport";
		case TypeInt: return "TypeInt";
		case TypeExec: return "TypeExec";
		case TypeExtendAction: return "TypeExtendAction";
		case TypeExtendComponent: return "TypeExtendComponent";
		case TypeExtendStruct: return "TypeExtendStruct";
		case TypePackage: return "TypePackage";
		case TypeString: return "TypeString";
		case TypeStruct: return "TypeStruct";
		case TypeRegistry: return "TypeRegistry";
		case TypeRef: return "TypeRef";
	}

	return "Unknown";
}

bool Type::insideInstance() {
	bool ret = false;

	// Traverse up through my hierarchy looking for
//	Type *
//	Type *
//
//	while (c != nullptr && cp != nullptr) {
//		if (c->getObjectType() == IObjectType::Action &&
//				cp->getObjectType() == IObjectType::Action) {
//			ret = true;
//			break;
//		}
//		c = cp;
//		cp = cp->getParent();
//	}

	return ret;
}


} /* namespace psi */
