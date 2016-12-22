/*
 * attr_item.h
 *
 * Copyright 2016 Mentor Graphics Corporation
 * All Rights Reserved Worldwide
 *
 * Licensed under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in
 *  compliance with the License.  You may obtain a copy of
 *  the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in
 * writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.  See
 * the License for the specific language governing
 * permissions and limitations under the License.
 * 
 *
 *  Created on: Jul 8, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_FIELD_ITEM_IMP_H
#define INCLUDED_FIELD_ITEM_IMP_H
#include <string>
#include "classlib/attr_item.h"
#include "ExprImp.h"
#include "NamedBaseItemImp.h"
#include "classlib/method_param_list.h"
#include "InlineExecUtil.h"

namespace pss {

class FieldItemImp: public NamedBaseItemImp {
public:
	friend class attr_item;
	FieldItemImp(
			attr_item 				*master,
			base_item 				*p,
			const std::string 		&name,
			const expr				*array_dim,
			attr_item::FieldAttr	attr,
			base_item				*wrapper,
			BaseItemImp				*type_hndl);

	virtual ~FieldItemImp();

	BaseItemImp *getDataType() const { return m_data_type; }

	void setDataType(BaseItemImp *dt);

	attr_item::FieldAttr getAttr() const { return m_attr; }

	void setAttr(attr_item::FieldAttr attr) { m_attr = attr; }

	void setInternal(bool i) { m_internal = i; }

	bool isInternal() const { return m_internal; }

	bool hasArrayDim() const { return m_has_array_dim; }

	const ExprImp &arrayDim() const { return m_array_dim; }

private:
	BaseItemImp				*m_data_type;
	attr_item::FieldAttr	m_attr;
	bool					m_internal;

	bool					m_has_array_dim;
	ExprImp					m_array_dim;
	InlineExecUtil			m_utils;

};

} /* namespace pss */

#endif /* INCLUDED_FIELD_ITEM_H */
