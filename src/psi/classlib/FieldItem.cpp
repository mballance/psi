/*
 * FieldItem.cpp
 *
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#include "FieldItem.h"

namespace psi {

FieldItem::FieldItem(BaseItem *p, const std::string &name) :
		NamedBaseItem(BaseItem::TypeField, p, name), m_data_type(0),
		m_attr(AttrNone) {

}

FieldItem::~FieldItem() {
	// TODO Auto-generated destructor stub
}


} /* namespace psi */
