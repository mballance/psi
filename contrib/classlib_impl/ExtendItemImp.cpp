/*
 * ExtendItem.cpp
 *
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#include "ExtendItemImp.h"

namespace psi {

ExtendItem::ExtendItem(BaseItem *p) :
		BaseItem(new ExtendItemImp(this, p, BaseItemImp::TypeExtendAction)) {
	// TODO: need to pass through an extension type
}

ExtendItemImp::ExtendItemImp(ExtendItem *master, BaseItem *p, BaseItemImp::ObjectType t) :
		BaseItemImp(master, t, toImp(p)), m_data_type(0) {

}

void ExtendItem::setDataType(BaseItem *t) {
	static_cast<ExtendItemImp *>(impl())->setDataType(t);
}

void ExtendItemImp::setDataType(BaseItem *t) {
	m_data_type = toImp(t);
}

ExtendItem::~ExtendItem() {
	// TODO Auto-generated destructor stub
}

ExtendItemImp::~ExtendItemImp() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
