/*
 * BindImpl.h
 *
 *  Created on: May 23, 2016
 *      Author: ballance
 */

#ifndef IMPL_BINDIMPL_H_
#define IMPL_BINDIMPL_H_
#include <vector>
#include "psi_api.h"

using namespace psi_api;

namespace psi {

class BindImpl: public IBind {
public:
	BindImpl(const std::vector<IBindPath *> &targets);

	virtual ~BindImpl();

	virtual IBaseItem::ItemType getType() const { return IBaseItem::TypeBind; }

	virtual IBaseItem *clone() { return 0; /* TODO: */ }

	virtual IBaseItem *getParent() const { return m_parent; }

	virtual void setParent(IBaseItem *parent) { m_parent = parent; }

	virtual const std::vector<IBindPath *> &getTargets() const { return m_targets; }

private:
	std::vector<IBindPath *>				m_targets;
	IBaseItem								*m_parent;


};

} /* namespace psi */

#endif /* IMPL_BINDIMPL_H_ */
