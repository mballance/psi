/*
 * ResourceStruct.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef RESOURCESTRUCT_H_
#define RESOURCESTRUCT_H_
#include <string>

#include "classlib/Bit.h"
#include "classlib/Rand.h"
#include "classlib/Struct.h"

namespace psi {

template <class T> class TypeRgy;

class ResourceStruct : public Struct {
	friend TypeRgy<ResourceStruct>;

	public:
		Rand<psi::Bit<31,0> >			instance_id;

	public:

		ResourceStruct(
				Type 				*p,
				const std::string 	&name,
				Struct 				*super_type=0);

		virtual ~ResourceStruct();

	private:
		ResourceStruct(Type *p);
};

} /* namespace psi */

#endif /* RESOURCESTRUCT_H_ */
