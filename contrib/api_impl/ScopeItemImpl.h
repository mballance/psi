/*
 * ScopeItemImpl.h
 *
 *  Created on: Aug 15, 2016
 *      Author: ballance
 */

#ifndef CONTRIB_API_IMPL_SCOPEITEMIMPL_H_
#define CONTRIB_API_IMPL_SCOPEITEMIMPL_H_
#include "api/IScopeItem.h"

using namespace psi_api;

namespace psi {

class ScopeItemImpl : public virtual IScopeItem {
public:
	ScopeItemImpl();

	virtual ~ScopeItemImpl();

	virtual const std::vector<IBaseItem *> &getItems() const;

	virtual void remove(IBaseItem *it);

	virtual void add(IBaseItem *item);

	/**
	 * Locates and returns the named field. Returns 0 if
	 * the named field does not exist
	 */
	virtual IField *getField(const std::string &name);

private:
	std::vector<IBaseItem *>				m_children;

};

} /* namespace psi */

#endif /* CONTRIB_API_IMPL_SCOPEITEMIMPL_H_ */
