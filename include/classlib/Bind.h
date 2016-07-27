/*
 * Bind.h
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_BIND_H
#define INCLUDED_BIND_H
#include <vector>
#include <functional>
#include "classlib/BaseItem.h"
#include "classlib/Types.h"

namespace psi {

class Bind: public BaseItem {
public:
	Bind(BaseItem *p, BaseItem &i1, BaseItem &i2);

	Bind(BaseItem *p, BaseItem &i1, BaseItem &i2, BaseItem &i3);

	Bind(BaseItem *p, BaseItem &i1, BaseItem &i2, BaseItem &i3, BaseItem &i4);

	Bind(BaseItem *p, BaseItem &i1, BaseItem &i2, BaseItem &i3, BaseItem &i4, BaseItem &i5);

	Bind(BaseItem *p, const std::vector<BaseItem *> &items);

	virtual ~Bind();

protected:


};

} /* namespace psi */

#endif /* INCLUDED_BIND_H */
