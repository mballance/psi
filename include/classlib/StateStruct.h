/*
 * StateStruct.h
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_STATE_STRUCT_H
#define INCLUDED_STATE_STRUCT_H

#include <string>
#include <vector>
#include "classlib/Struct.h"
#include "classlib/Rand.h"
#include "classlib/Bool.h"

namespace psi {

class Scope;
class StateStruct: public Struct {
public:

	Rand<Bool>			initial;

	StateStruct(const Scope &p);

	virtual ~StateStruct();

};

} /* namespace psi */

#endif /* INCLUDED_STATE_STRUCT_H */
