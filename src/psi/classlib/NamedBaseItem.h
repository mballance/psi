/*
 * NamedBaseItem.h
 *
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_CLASSLIB_NAMEDBASEITEM_H_
#define SRC_PSI_CLASSLIB_NAMEDBASEITEM_H_

#include <string>
#include "classlib/BaseItem.h"

namespace psi {

class NamedBaseItem: public BaseItem {
public:
	NamedBaseItem(BaseItem::ObjectType t, BaseItem *p, const std::string &name="");

	virtual ~NamedBaseItem();

	virtual const std::string &getName() const { return m_name; }

	void setName(const std::string &name) { m_name = name; }

	static NamedBaseItem *to(BaseItem *it);

	static std::string getName(BaseItem *it);

private:
	std::string					m_name;
};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_NAMEDBASEITEM_H_ */
