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
	Bind(BaseItem *p, FieldItem &i1, FieldItem &i2);

	Bind(BaseItem *p, FieldItem &i1, FieldItem &i2, FieldItem &i3);

	Bind(BaseItem *p, FieldItem &i1, FieldItem &i2, FieldItem &i3, FieldItem &i4);

	Bind(BaseItem *p, FieldItem &i1, FieldItem &i2, FieldItem &i3, FieldItem &i4, FieldItem &i5);

	Bind(BaseItem *p, const std::vector<FieldItem *> &items);

	virtual ~Bind();

	const std::vector<FieldItem *> &getItems() const { return m_items; }

private:
	std::vector<FieldItem *>					m_items;
};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_BIND_H_ */
