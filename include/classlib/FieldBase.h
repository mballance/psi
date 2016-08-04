/*
 * FieldBase.h
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
 */
#ifndef INCLUDED_FIELD_BASE_H
#define INCLUDED_FIELD_BASE_H
#include "classlib/FieldItem.h"
#include "classlib/TypeDecl.h"

namespace pss {

template <class T> class FieldBase : public T {
public:

	virtual ~FieldBase() { }

	/*
	 * Provide an explicit conversion function to tell the
	 * compiler how to interpret the fact that both we and T extend
	 * from BaseItem
	 */
	operator Expr() const { return Expr(m_field); }

	operator const FieldItem &() const { return m_field; }

protected:

	FieldBase(FieldItem::FieldAttr attr, BaseItem *p, const std::string &name) : T(Scope(true)),
		m_field(p, name, attr, this, (TypeDecl<T>::valid())?TypeDecl<T>::id():0) {
	}


protected:
	FieldItem						m_field;

};

}

#endif /* INCLUDED_FIELD_BASE_H */

