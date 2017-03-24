/*
 * output.h
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

#ifndef INCLUDED_OUTPUT_H
#define INCLUDED_OUTPUT_H
#include <string>
#include <stdio.h>

#include "type_decl.h"

namespace pss {

class action;
template <class T> class output : public vendor::output_impl<T> {
public:
		/**
		 * This constructor is used to specify an action output field
		 */
		output(const scope &scope);

		virtual ~output() { }

};


} /* namespace pss */

#endif /* INCLUDED_OUTPUT_H */