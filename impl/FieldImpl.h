/*
 * FieldImpl.h
 *
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
 *  Created on: May 5, 2016
 *      Author: ballance
 */

#ifndef IMPL_FIELDIMPL_H_
#define IMPL_FIELDIMPL_H_
#include "api/IField.h"

using namespace psi_api;

namespace psi {

class FieldImpl: public IField {
public:

	FieldImpl(
			const std::string 	&name,
			IBaseItem 			*field_type,
			IField::FieldAttr 	attr);

	virtual ~FieldImpl();

	virtual IBaseItem::ItemType getType() const { return IBaseItem::TypeField; }

	virtual IBaseItem *clone();

	virtual IBaseItem *getParent() const { return m_parent; }

	void setParent(IBaseItem *p) { m_parent = p; }

	virtual const std::string &getName() const { return m_name; }

	virtual IBaseItem *getDataType() const { return m_field_type; }

	virtual FieldAttr getAttr() const { return m_attr; }

	virtual IFieldRef *getFieldRef();



private:
	IBaseItem					*m_parent;
	std::string					m_name;
	IBaseItem					*m_field_type;
	FieldAttr					m_attr;
	IFieldRef					*m_field_ref;

};

} /* namespace psi */

#endif /* IMPL_FIELDIMPL_H_ */
