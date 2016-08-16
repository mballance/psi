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
#include "api/IBind.h"
#include "BaseItemImpl.h"

using namespace psi_api;

namespace psi {

class BindImpl: public virtual IBind, public virtual BaseItemImpl {
public:
	BindImpl(const std::vector<IBindPath *> &targets);

	virtual ~BindImpl();

	virtual const std::vector<IBindPath *> &getTargets() const { return m_targets; }

private:
	std::vector<IBindPath *>				m_targets;

};

} /* namespace psi */

#endif /* IMPL_BINDIMPL_H_ */
