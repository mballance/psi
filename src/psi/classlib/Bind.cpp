/*
 * Bind.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#include "Bind.h"

namespace psi {

Bind::Bind(Type *p, Type &i1, Type &i2) : Type(TypeBind, p) {
	m_items.push_back(&i1);
	m_items.push_back(&i2);
}

Bind::Bind(Type *p, Type &i1, Type &i2, Type &i3) : Type(TypeBind, p) {
	m_items.push_back(&i1);
	m_items.push_back(&i2);
	m_items.push_back(&i3);
}

Bind::Bind(Type *p, Type &i1, Type &i2, Type &i3,
		Type &i4) : Type(TypeBind, p) {
	m_items.push_back(&i1);
	m_items.push_back(&i2);
	m_items.push_back(&i3);
	m_items.push_back(&i4);
}

Bind::Bind(Type *p, Type &i1, Type &i2, Type &i3,
		Type &i4, Type &i5) : Type(TypeBind, p) {
	m_items.push_back(&i1);
	m_items.push_back(&i2);
	m_items.push_back(&i3);
	m_items.push_back(&i4);
	m_items.push_back(&i5);
}


Bind::Bind(Type *p, const std::vector<Type *> &items) :
		Type(TypeBind, p), m_items(items) {

}

Bind::~Bind() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
