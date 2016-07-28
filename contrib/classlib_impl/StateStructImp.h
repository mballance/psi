/*
 * StateStruct.h
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_STATE_STRUCT_IMP_H
#define INCLUDED_STATE_STRUCT_IMP_H

#include <string>
#include <vector>
#include "classlib/StateStruct.h"
#include "StructImp.h"

namespace psi {

class ScopeImp;
class StateStructImp : public StructImp {
public:

	StateStructImp(StateStruct *master, ScopeImp *p);

	virtual ~StateStructImp();

};

} /* namespace psi */

#endif /* INCLUDED_STATE_STRUCT_H */
