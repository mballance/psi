/*
 * Input.h
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

#ifndef INPUT_H_
#define INPUT_H_
#include <string>

#include "classlib/FieldItem.h"
#include "classlib/TypeDecl.h"

namespace psi {

template <class T> class Input : public T {

	public:
		Input(BaseItem *p, const std::string &name) : T(Scope(true)), m_field(p, name) {
			m_field.setAttr(FieldItem::AttrInput);
			m_field.setDataType(TypeDecl<T>::type_id());
		}

		virtual ~Input() { }

	private:

		FieldItem					m_field;
};

} /* namespace psi */

#endif /* INPUT_H_ */
