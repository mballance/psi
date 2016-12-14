/*
 * pss_int.h
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
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#ifndef INT_H_
#define INT_H_
#include "classlib/IntType.h"

namespace pss {

template <int MSB=31, int LSB=0> class pss_int : public IntType {

	public:

		pss_int(const Scope &p) : IntType(0, MSB, LSB) { }

		pss_int(const std::string &name) :
			IntType(name, MSB, LSB) { }

};

/**
 * Convenience typedefs
 */
typedef pss_int<7,0>  pss_int8_t;
typedef pss_int<15,0> pss_int16_t;
typedef pss_int<31,0> pss_int32_t;
typedef pss_int<63,0> pss_int64_t;

}



#endif /* INT_H_ */
