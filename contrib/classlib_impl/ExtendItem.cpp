/*
 * ExtendItem.cpp
 *
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#include "ExtendItem.h"

namespace psi {

ExtendItem::ExtendItem(const Scope &p, BaseItem::ObjectType t) :
		BaseItem(t, this), m_data_type(0) {

}

ExtendItem::~ExtendItem() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
