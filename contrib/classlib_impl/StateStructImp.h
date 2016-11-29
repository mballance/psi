/*
 * StateStruct.h
 *
 * Copyright 2016 Mentor Graphics Corporation
 * All Rights Reserved Worldwide
 *
 * Licensed under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in
 *  compliance with the License.  You may obtain a copy of
 *  the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in
 * writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.  See
 * the License for the specific language governing
 * permissions and limitations under the License.
 * 
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

namespace pss {

class ScopeImp;
class StateStructImp : public StructImp {
public:

	StateStructImp(StateStruct *master, ScopeImp *p);

	virtual ~StateStructImp();

};

} /* namespace pss */

#endif /* INCLUDED_STATE_STRUCT_H */
