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
#include "classlib/With.h"

namespace psi {

template <class T> class Field : public T {
	public:

		Field(BaseItem *p, const std::string &name) : T(Scope(true)), m_field(p, name) {
			T *t = static_cast<T *>(this);

			// Get the 'authoratative' type declaration from
			// TypeDecl<> in the case of a user-defined type. Otherwise,
			// just set the type handle
			if (t->getObjectType() == BaseItem::TypeAction ||
					t->getObjectType() == BaseItem::TypeStruct ||
					t->getObjectType() == BaseItem::TypeComponent) {
				m_field.setDataType(TypeDecl<T>::type_id());
			} else {
				m_field.setDataType(t);
			}
		}

		virtual ~Field() { }

		virtual const std::string  &getName() const {
			return m_field.getName();
		}

		/*
		 * Provide an explicit conversion function to tell the
		 * compiler how to interpret the fact that both we and T extend
		 * from BaseItem
		 */
		operator Expr() const { return Expr(m_field); }

		operator const FieldItem &() const { return m_field; }

		With with(const ExprList &l) const { return With(m_field, l); }

	private:
		FieldItem						m_field;
};

}




#endif /* SRC_CLASSLIB_FIELD_H_ */
