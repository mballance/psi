/*
 * export_item.cpp
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
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#include "ExportItemImp.h"

namespace pss {

export_item::export_item(base_item	*p) : base_item(new ExportItemImp(this, p)) {

}

ExportItemImp::ExportItemImp(
		export_item		*master,
		base_item		*p) :
	BaseItemImp(master, BaseItemImp::TypeExportItem, p), m_data_type(0) {
}

export_item::export_item(
		base_item 			*p,
		const expr_list		&exp_params) :
	base_item(new ExportItemImp(this, p, exp_params)) {
//	setTypeData(t_ref);
}

ExportItemImp::ExportItemImp(
		export_item			*master,
		base_item 			*p,
		const expr_list		&exp_params) :
	BaseItemImp(master, BaseItemImp::TypeExportItem, p),
	m_exp_params(exp_params), m_data_type(0) {
//	setTypeData(t_ref);
}

void export_item::setDataType(base_item *t) {
	static_cast<ExportItemImp *>(impl())->setDataType(t);
}

void ExportItemImp::setDataType(base_item *t) {
	m_data_type = (t)?t->impl():0;
}

BaseItemImp *ExportItemImp::getDataType() const {
	return m_data_type;
}

export_item::~export_item() {
	// TODO Auto-generated destructor stub
}

}
