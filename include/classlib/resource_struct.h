/*
 * resource_struct.h
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
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_RESOURCE_STRUCT_H
#define INCLUDED_RESOURCE_STRUCT_H
#include <string>

#include "classlib/pss_bit.h"
#include "classlib/rand_attr.h"
#include "classlib/pss_struct.h"

namespace pss {

class resource_struct : public pss_struct {
public:
//TODO:		rand_attr<pss::pss_bit<uint32_t> >			instance_id;

public:
		virtual ~resource_struct();

protected:
		resource_struct(const Scope &p);

};

} /* namespace pss */

#endif /* INCLUDED_RESOURCE_STRUCT_H */
