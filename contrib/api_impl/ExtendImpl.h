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
#include "api/IField.h"
#include "BaseItemImpl.h"
#include "ScopeItemImpl.h"

using namespace psi_api;

namespace psi {

class ExtendImpl:
		public virtual IExtend,
		public virtual BaseItemImpl,
		public virtual ScopeItemImpl {
public:
	ExtendImpl(IBaseItem *target);
	virtual ~ExtendImpl();

	virtual ExtendType getExtendType() const { return m_extendType; }

	virtual IBaseItem *getTarget() const { return m_target; }

private:
	IExtend::ExtendType				m_extendType;
	IBaseItem						*m_target;

};

} /* namespace psi */

#endif /* IMPL_EXTENDIMPL_H_ */
