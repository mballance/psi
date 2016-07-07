/*
 * Bind.cpp
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#include "Bind.h"

namespace psi {

Bind::Bind(BaseItem *p, BaseItem &i1, BaseItem &i2) : BaseItem(TypeBind, p) {
	m_items.push_back(&i1);
	m_items.push_back(&i2);
}

Bind::Bind(BaseItem *p, BaseItem &i1, BaseItem &i2, BaseItem &i3) : BaseItem(TypeBind, p) {
	m_items.push_back(&i1);
	m_items.push_back(&i2);
	m_items.push_back(&i3);
}

Bind::Bind(BaseItem *p, BaseItem &i1, BaseItem &i2, BaseItem &i3,
		BaseItem &i4) : BaseItem(TypeBind, p) {
	m_items.push_back(&i1);
	m_items.push_back(&i2);
	m_items.push_back(&i3);
	m_items.push_back(&i4);
}

Bind::Bind(BaseItem *p, BaseItem &i1, BaseItem &i2, BaseItem &i3,
		BaseItem &i4, BaseItem &i5) : BaseItem(TypeBind, p) {
	m_items.push_back(&i1);
	m_items.push_back(&i2);
	m_items.push_back(&i3);
	m_items.push_back(&i4);
	m_items.push_back(&i5);
}


Bind::Bind(BaseItem *p, const std::vector<BaseItem *> &items) :
		BaseItem(TypeBind, p), m_items(items) {

}

Bind::~Bind() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
