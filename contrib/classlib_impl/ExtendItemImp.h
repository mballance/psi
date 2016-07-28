/*
 * ExtendItem.h
 *
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_EXTEND_ITEM_IMP_H
#define INCLUDED_EXTEND_ITEM_IMP_H

#include "classlib/ExtendItem.h"
#include "BaseItemImp.h"

namespace psi {

class ExtendItemImp: public BaseItemImp {
public:
	ExtendItemImp(ExtendItem *master, BaseItem *p, BaseItemImp::ObjectType t);

	virtual ~ExtendItemImp();

	void setDataType(BaseItem *dt);

	BaseItemImp *getDataType() const { return m_data_type; }

private:

	BaseItemImp				*m_data_type;
};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_EXTENDITEM_H_ */
