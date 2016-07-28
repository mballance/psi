/*
 * BindImp.h
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_BIND_IMP_H
#define INCLUDED_BIND_IMP_H
#include <vector>
#include <functional>
#include "BaseItemImp.h"
#include "classlib/Bind.h"

namespace psi {

class BindImp: public BaseItemImp {
public:

	BindImp(Bind *master, BaseItemImp *p);

	virtual ~BindImp();

protected:

};

} /* namespace psi */

#endif /* INCLUDED_BIND_IMPL_H */
