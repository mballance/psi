/*
 * Output.h
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

#ifndef OUTPUT_H_
#define OUTPUT_H_
#include <string>
#include <stdio.h>

#include "classlib/Type.h"

namespace psi {

// TODO: may need an OutputBase class to enable binding
template <class T> class Output : public T {

	public:
		Output(Type *p, const std::string &name) : T(p, name) {
			static_cast<Type *>(this)->setIsOutput(true);
			static_cast<Type *>(this)->setTypeData(TypeRgy<T>::type_id());
		}

		virtual ~Output() { }
};

} /* namespace psi */

#endif /* OUTPUT_H_ */
