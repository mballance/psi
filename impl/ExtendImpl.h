/*
 * ExtendImpl.h
 *
 *  Created on: May 18, 2016
 *      Author: ballance
 */

#ifndef IMPL_EXTENDIMPL_H_
#define IMPL_EXTENDIMPL_H_
#include <vector>
#include "api/IExtend.h"

using namespace psi_api;

namespace psi {

class ExtendImpl: public IExtend {
public:
	ExtendImpl(IBaseItem *target);
	virtual ~ExtendImpl();

	virtual IBaseItem::ItemType getType() const { return IBaseItem::TypeExtend; }

	virtual IBaseItem *clone() { return 0; }

	virtual IBaseItem *getParent() const { return m_parent; }

	virtual void setParent(IBaseItem *p) { m_parent = p; }

	virtual ExtendType getExtendType() const { return m_extendType; }

	virtual IBaseItem *getTarget() const { return m_target; }

	virtual const std::vector<IBaseItem *> &getItems() const { return m_items; }

	virtual void add(IBaseItem *it);

private:
	IExtend::ExtendType				m_extendType;
	IBaseItem						*m_target;

	IBaseItem						*m_parent;
	std::vector<IBaseItem *>		m_items;

};

} /* namespace psi */

#endif /* IMPL_EXTENDIMPL_H_ */
