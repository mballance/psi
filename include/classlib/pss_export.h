/*
 * pss_export.h
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
 *  Created on: Jul 13, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_EXPORT_H
#define INCLUDED_EXPORT_H
#include "classlib/export_item.h"
#include "classlib/type_decl.h"
#include "classlib/method_param_list.h"

namespace pss {

template <class T> class pss_export : public T {
public:
	pss_export(base_item *p) : T(scope(true)), m_item(p) {
		m_item.setDataType(type_decl<T>::id());
	}

	pss_export(base_item *p, const method_param_list &exp_params) : T(scope(true)), m_item(p, exp_params) {
		m_item.setDataType(type_decl<T>::id());
	}

private:
	export_item				m_item;


};

}


#endif /* SRC_PSI_CLASSLIB_EXPORT_H_ */
