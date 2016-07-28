/*
 * ExtendItem.cpp
 *
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#include "ExtendItemImp.h"
#include "ScopeImp.h"

namespace psi {

ExtendItem::ExtendItem(const Scope &p) :
		BaseItem(new ExtendItemImp(this, p.impl()->parent(), BaseItemImp::TypeExtendAction)) {
	// TODO: need to pass through an extension type
}

ExtendItemImp::ExtendItemImp(ExtendItem *master, BaseItemImp *p, BaseItemImp::ObjectType t) :
		BaseItemImp(master, t, p), m_data_type(0) {

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
