/*
 * Rand.h
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
 *
 *  Created on: Apr 25, 2016
 *      Author: ballance
 */

#ifndef SRC_RAND_H_
#define SRC_RAND_H_
#include <string>

#include "classlib/BaseItem.h"
#include "classlib/TypeRgy.h"

namespace psi {

template <class T> class Rand : public T {

	public:
		Rand(BaseItem *p, const std::string &name) : T(p, name) {
			BaseItem *t = static_cast<BaseItem *>(this);
			t->setAttr(BaseItem::AttrRand);
			if (t->getObjectType() == BaseItem::TypeStruct) {
				t->setTypeData(TypeRgy<T>::type_id());
			}
		}

		virtual ~Rand() { };

};

} /* namespace psi */

#endif /* SRC_RAND_H_ */
