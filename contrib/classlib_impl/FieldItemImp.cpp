/*
 * FieldItem.cpp
 *
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#include "FieldItemImp.h"

namespace psi {

FieldItem::FieldItem(BaseItem *p, const std::string &name, FieldItem::FieldAttr attr) :
		BaseItem(new FieldItemImp(this, p, name, attr)) {

}

FieldItemImp::FieldItemImp(
		FieldItem 				*master,
		BaseItem 				*p,
		const std::string 		&name,
		FieldItem::FieldAttr	attr) :
	NamedBaseItemImp(master, BaseItemImp::TypeField, toImp(p), name),
		m_data_type(0), m_attr(attr), m_internal(false) {

}

FieldItem::~FieldItem() {
	// TODO Auto-generated destructor stub
}

FieldItemImp::~FieldItemImp() {
	// TODO Auto-generated destructor stub
}

void FieldItem::setDataType(BaseItem *dt) {
	static_cast<FieldItemImp *>(impl())->setDataType(dt);
}

void FieldItemImp::setDataType(BaseItem *dt) {
	m_data_type = toImp(dt);
}


} /* namespace psi */
