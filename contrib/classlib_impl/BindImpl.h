/*
 * BindImpl.h
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_BIND_IMPL_H
#define INCLUDED_BIND_IMPL_H
#include <vector>
#include <functional>
#include "BaseItemImpl.h"
#include "classlib/Bind.h"

namespace psi {

class BindImpl: public BaseItemImpl {
public:

	BindImpl(Bind *master, BaseItemImpl *p);

	virtual ~BindImpl();

protected:

};

} /* namespace psi */

#endif /* INCLUDED_BIND_IMPL_H */
