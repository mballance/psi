/*
 * NamedScopeItem.h
 *
 *  Created on: May 3, 2016
 *      Author: ballance
 */

#ifndef IMPL_NAMEDSCOPEITEMIMPL_H_
#define IMPL_NAMEDSCOPEITEMIMPL_H_
#include "api/INamedItem.h"
#include "api/IScopeItem.h"

using namespace psi_api;

namespace psi {

class NamedScopeItemImpl : public virtual INamedItem, public IScopeItem {

public:
	NamedScopeItemImpl(IBaseItem::ItemType t, const std::string &name);

	virtual ~NamedScopeItemImpl();

	virtual IBaseItem::ItemType getType() const { return m_type; }

	virtual const std::string &getName() const { return m_name; }

	virtual const std::vector<IBaseItem *> &getItems() const { return m_children; }

	virtual void add(IBaseItem *item);

protected:
	IBaseItem::ItemType			m_type;
	std::string					m_name;
	std::vector<IBaseItem *>	m_children;

};
}

#endif /* IMPL_NAMEDSCOPEITEMIMPL_H_ */
