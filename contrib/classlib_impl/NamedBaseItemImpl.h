/*
 * NamedBaseItem.h
 *
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_NAMED_BASE_ITEM_IMPL_H
#define INCLUDED_NAMED_BASE_ITEM_IMPL_H

#include <string>
#include "BaseItemImpl.h"

namespace psi {

class NamedBaseItemImpl : public BaseItemImpl {
public:
	NamedBaseItemImpl(
			BaseItem 					*master,
			BaseItemImpl::ObjectType 	t,
			BaseItemImpl 				*p,
			const std::string 			&name="");

	virtual ~NamedBaseItemImpl();

	virtual const std::string &getName() const { return m_name; }

	void setName(const std::string &name) { m_name = name; }

	static NamedBaseItemImpl *to(BaseItemImpl *it);

	static std::string getName(BaseItemImpl *it);

private:
	std::string					m_name;
};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_NAMEDBASEITEM_H_ */
