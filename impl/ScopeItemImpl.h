/*
 * ScopeItemImpl.h
 *
 *  Created on: May 2, 2016
 *      Author: ballance
 */

#ifndef IMPL_SCOPEITEMIMPL_H_
#define IMPL_SCOPEITEMIMPL_H_
#include <vector>
#include "api/IScopeItem.h"
#include "BaseItemImpl.h"

using namespace psi_api;

namespace psi {

class ScopeItemImpl : public virtual IScopeItem, public BaseItemImpl {
	public:
		ScopeItemImpl(IBaseItem::ItemType t);

		virtual ~ScopeItemImpl();

		virtual const std::vector<IBaseItem *> &getItems() const;

		virtual void add(IBaseItem *item);

	protected:

		std::vector<IBaseItem *>			m_children;
};

} /* namespace psi */

#endif /* IMPL_SCOPEITEMIMPL_H_ */
