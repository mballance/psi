/*
 * NamedBaseItem.h
 *
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_NAMED_BASE_ITEM_IMP_H
#define INCLUDED_NAMED_BASE_ITEM_IMP_H

#include <string>
#include "BaseItemImp.h"

namespace psi {

class NamedBaseItemImp : public BaseItemImp {
public:
	NamedBaseItemImp(
			BaseItem 					*master,
			BaseItemImp::ObjectType 	t,
			BaseItemImp 				*p,
			const std::string 			&name="");

	virtual ~NamedBaseItemImp();

	virtual const std::string &getName() const { return m_name; }

	void setName(const std::string &name) { m_name = name; }

	static NamedBaseItemImp *to(BaseItemImp *it);

	static std::string getName(BaseItemImp *it);

private:
	std::string					m_name;
};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_NAMEDBASEITEM_H_ */
