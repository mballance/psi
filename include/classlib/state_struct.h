/*
 * state_struct.h
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

#ifndef INCLUDED_STATE_STRUCT_H
#define INCLUDED_STATE_STRUCT_H

#include <string>
#include <vector>
#include "classlib/pss_struct.h"
#include "classlib/rand_attr.h"
#include "classlib/pss_bool.h"

namespace pss {

class scope;
class state_struct: public pss_struct {
public:

	rand_attr<bool>			initial;

	virtual ~state_struct();

protected:
	state_struct(const scope &p);

};

} /* namespace pss */

#endif /* INCLUDED_STATE_STRUCT_H */
