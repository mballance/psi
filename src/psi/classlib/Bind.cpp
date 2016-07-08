/*
 * Bind.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#include "Bind.h"

namespace psi {

Bind::Bind(BaseItem *p, FieldItem &i1, FieldItem &i2) : BaseItem(TypeBind, p) {
	m_items.push_back(&i1);
	m_items.push_back(&i2);
}

Bind::Bind(BaseItem *p, FieldItem &i1, FieldItem &i2, FieldItem &i3) : BaseItem(TypeBind, p) {
	m_items.push_back(&i1);
	m_items.push_back(&i2);
	m_items.push_back(&i3);
}

Bind::Bind(BaseItem *p, FieldItem &i1, FieldItem &i2, FieldItem &i3,
		FieldItem &i4) : BaseItem(TypeBind, p) {
	m_items.push_back(&i1);
	m_items.push_back(&i2);
	m_items.push_back(&i3);
	m_items.push_back(&i4);
}

Bind::Bind(BaseItem *p, FieldItem &i1, FieldItem &i2, FieldItem &i3,
		FieldItem &i4, FieldItem &i5) : BaseItem(TypeBind, p) {
	m_items.push_back(&i1);
	m_items.push_back(&i2);
	m_items.push_back(&i3);
	m_items.push_back(&i4);
	m_items.push_back(&i5);
}


Bind::Bind(BaseItem *p, const std::vector<FieldItem *> &items) :
		BaseItem(TypeBind, p), m_items(items) {

}

Bind::~Bind() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
