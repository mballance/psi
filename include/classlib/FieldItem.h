/*
 * FieldItem.h
 *
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_FIELD_ITEM_H
#define INCLUDED_FIELD_ITEM_H
#include <string>
#include "classlib/BaseItem.h"

namespace psi {

class FieldItem: public BaseItem {
public:
	enum FieldAttr {
		AttrNone = 0,
		AttrInput,
		AttrOutput,
		AttrLock,
		AttrShare,
		AttrRand,
		AttrPool
	};

public:
	FieldItem(BaseItem *p, const std::string &name, FieldAttr attr);

	virtual ~FieldItem();

	void setDataType(BaseItem *dt);

};

} /* namespace psi */

#endif /* INCLUDED_FIELD_ITEM_H */
