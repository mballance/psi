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
#include "BaseItemImpl.h"
#include "NamedItemImpl.h"

using namespace psi_api;

namespace psi {

class FieldImpl:
		public virtual IField,
		public virtual BaseItemImpl,
		public virtual NamedItemImpl {
public:

	FieldImpl(
			const std::string 	&name,
			IBaseItem 			*field_type,
			IField::FieldAttr 	attr,
			IExpr				*array_dim);

	virtual ~FieldImpl();

	virtual IBaseItem *getDataType() const { return m_field_type; }

	virtual void setDataType(IBaseItem *type) { m_field_type = type; }

	virtual FieldAttr getAttr() const { return m_attr; }

	virtual IExpr *getArrayDim() const { return m_array_dim; }



private:
	IBaseItem					*m_field_type;
	FieldAttr					m_attr;
	IExpr						*m_array_dim;

};

} /* namespace psi */

#endif /* IMPL_FIELDIMPL_H_ */
