/*
 * ExtendItem.h
 *
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_CLASSLIB_EXTENDITEM_H_
#define SRC_PSI_CLASSLIB_EXTENDITEM_H_

#include "classlib/BaseItem.h"
#include "classlib/Scope.h"

namespace psi {

class ExtendItem: public BaseItem {
public:
	ExtendItem(const Scope &p, BaseItem::ObjectType t);

	virtual ~ExtendItem();

	void setDataType(BaseItem *dt) { m_data_type = dt; }

	BaseItem *getDataType() const { return m_data_type; }

private:

	BaseItem				*m_data_type;
};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_EXTENDITEM_H_ */
