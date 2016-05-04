/*
 * ComponentImpl.h
 *
 *  Created on: May 3, 2016
 *      Author: ballance
 */

#ifndef IMPL_COMPONENTIMPL_H_
#define IMPL_COMPONENTIMPL_H_
#include "api/IComponent.h"

namespace psi {

class ComponentImpl: public IComponent {

public:
	ComponentImpl(const std::string &name);

	virtual ~ComponentImpl();

	virtual IBaseItem::ItemType getType() const {
		return IBaseItem::TypeComponent;
	}

	virtual const std::string &getName() const;

	virtual const std::vector<IBaseItem *> &getItems() const;

	virtual void add(IBaseItem *it);


private:

	std::string					m_name;
	std::vector<IBaseItem *>	m_children;

};

} /* namespace psi */

#endif /* IMPL_COMPONENTIMPL_H_ */
