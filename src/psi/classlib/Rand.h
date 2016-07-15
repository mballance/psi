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

template <class T> class Rand : public T {

	public:
		Rand(BaseItem *p, const std::string &name) : T(true), m_field(p, name) {
			T *t = static_cast<T *>(this);

			m_field.setAttr(FieldItem::AttrRand);

			if (t->getObjectType() == BaseItem::TypeAction ||
					t->getObjectType() == BaseItem::TypeStruct) {
				m_field.setDataType(TypeDecl<T>::id());
			} else {
				m_field.setDataType(t);
			}
		}

		virtual ~Rand() { };

		/*
		 * Provide an explicit conversion function to tell the
		 * compiler how to interpret the fact that both we and T extend
		 * from BaseItem
		 */
		operator Expr() const { return Expr(static_cast<const FieldItem &>(m_field)); }

	private:

		FieldItem					m_field;

};

} /* namespace psi */

#endif /* SRC_RAND_H_ */
