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
	ExtendItem(BaseItem *p);

	virtual ~ExtendItem();

	void setDataType(BaseItem *dt);

};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_EXTENDITEM_H_ */
