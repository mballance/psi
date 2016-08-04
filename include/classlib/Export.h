/*
 * Export.h
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
 *  Created on: Jul 13, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_EXPORT_H
#define INCLUDED_EXPORT_H
#include "classlib/ExportItem.h"
#include "classlib/TypeDecl.h"

namespace pss {

template <class T> class Export : public T {
public:
	Export(BaseItem *p) : T(Scope(true)), m_item(p) {
		m_item.setDataType(TypeDecl<T>::id());
	}

	Export(BaseItem *p, const ExprList &exp_params) : T(Scope(true)), m_item(p, exp_params) {
		m_item.setDataType(TypeDecl<T>::id());
	}

private:
	ExportItem				m_item;


};

}


#endif /* SRC_PSI_CLASSLIB_EXPORT_H_ */
