/*
 * memory_struct.h
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

#ifndef INCLUDED_MEMORY_STRUCT_H
#define INCLUDED_MEMORY_STRUCT_H

#include "pss_struct.h"

namespace pss {


class memory_struct: public pss_struct {
public:
		virtual ~memory_struct();

protected:
		memory_struct(const scope &p);

	private:

};

} /* namespace pss */

#endif /* MEMORYSTRUCT_H_ */
