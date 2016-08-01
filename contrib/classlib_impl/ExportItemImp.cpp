/*
 * ExportItem.cpp
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
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#include "ExportItemImp.h"

namespace psi {

ExportItem::ExportItem(BaseItem	*p) : BaseItem(new ExportItemImp(this, p)) {

}

ExportItemImp::ExportItemImp(
		ExportItem		*master,
		BaseItem		*p) :
	BaseItemImp(master, BaseItemImp::TypeExportItem, p), m_data_type(0) {
}

ExportItem::ExportItem(
		BaseItem 			*p,
		const ExprList		&exp_params) :
	BaseItem(new ExportItemImp(this, p, exp_params)) {
//	setTypeData(t_ref);
}

ExportItemImp::ExportItemImp(
		ExportItem			*master,
		BaseItem 			*p,
		const ExprList		&exp_params) :
	BaseItemImp(master, BaseItemImp::TypeExportItem, p),
	m_exp_params(exp_params), m_data_type(0) {
//	setTypeData(t_ref);
}

void ExportItem::setDataType(BaseItem *t) {
	static_cast<ExportItemImp *>(impl())->setDataType(t);
}

void ExportItemImp::setDataType(BaseItem *t) {
	m_data_type = (t)?t->impl():0;
}

BaseItemImp *ExportItemImp::getDataType() const {
	return m_data_type;
}

ExportItem::~ExportItem() {
	// TODO Auto-generated destructor stub
}

}
