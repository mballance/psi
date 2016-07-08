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

#include "classlib/FieldItem.h"
#include "classlib/TypeDecl.h"

namespace psi {

template <class T> class Rand : public FieldItem, public T {

	public:
		Rand(BaseItem *p, const std::string &name) :
			FieldItem(p, name), T(Scope::ScopeType_FieldDecl) {
			T *t = static_cast<T *>(this);

			setAttr(FieldItem::AttrRand);

			if (t->getObjectType() == BaseItem::TypeAction ||
					t->getObjectType() == BaseItem::TypeStruct) {
				setDataType(TypeDecl<T>::id());
			} else {
				setDataType(t);
			}
		}

		virtual ~Rand() { };

};

} /* namespace psi */

#endif /* SRC_RAND_H_ */
