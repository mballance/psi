/*
 * Bind.h
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_CLASSLIB_BIND_H_
#define SRC_PSI_CLASSLIB_BIND_H_
#include <vector>
#include <functional>
#include "classlib/BaseItem.h"
#include "classlib/FieldItem.h"

namespace psi {

class Bind: public BaseItem {
public:
	Bind(BaseItem *p, BaseItem &i1, BaseItem &i2);

	Bind(BaseItem *p, BaseItem &i1, BaseItem &i2, BaseItem &i3);

	Bind(BaseItem *p, BaseItem &i1, BaseItem &i2, BaseItem &i3, BaseItem &i4);

	Bind(BaseItem *p, BaseItem &i1, BaseItem &i2, BaseItem &i3, BaseItem &i4, BaseItem &i5);

	Bind(BaseItem *p, const std::vector<BaseItem *> &items);

	virtual ~Bind();

	const std::vector<BaseItem *> &getItems() const { return m_items; }

private:
	std::vector<BaseItem *>					m_items;
};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_BIND_H_ */
