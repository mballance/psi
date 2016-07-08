/*
 * Field.h
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
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_CLASSLIB_FIELD_H_
#define SRC_CLASSLIB_FIELD_H_

#include <string>

#include "classlib/BaseItem.h"
#include "classlib/TypeDecl.h"
#include "classlib/FieldItem.h"

namespace psi {

template <class T> class Field : public FieldItem, public T {
	public:

		Field(BaseItem *p, const std::string &name) : FieldItem(p, name), T(p) {
			// Both FieldItem and T extend from BaseItem.
			// Ensure we don't get confused...
			FieldItem *f = static_cast<FieldItem *>(this);
			T *t = static_cast<T *>(this);

			// Get the 'authoratative' type declaration from
			// TypeDecl<> in the case of a user-defined type. Otherwise,
			// just set the type handle
			if (t->getObjectType() == BaseItem::TypeAction ||
					t->getObjectType() == BaseItem::TypeStruct ||
					t->getObjectType() == BaseItem::TypeComponent) {
				f->setDataType(TypeDecl<T>::type_id());
			} else {
				f->setDataType(t);
			}
		}
};

}




#endif /* SRC_CLASSLIB_FIELD_H_ */
