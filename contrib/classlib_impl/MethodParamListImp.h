/*
 * MethodParamListImp.h
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
 *  Created on: Aug 26, 2016
 *      Author: ballance
 */

#ifndef CONTRIB_CLASSLIB_IMPL_METHODPARAMLISTIMP_H_
#define CONTRIB_CLASSLIB_IMPL_METHODPARAMLISTIMP_H_
#include "classlib/method_param_list.h"

namespace pss {

class FieldItemImp;
class MethodParamListImp {
public:
	MethodParamListImp(method_param_list	*master);

	virtual ~MethodParamListImp();

	void add(const attr_item &rhs);

	const std::vector<attr_item> &parameters() const {
		return m_parameters;
	}

	void inc_refcnt();

	void dec_refcnt();

private:
	std::vector<attr_item>			m_parameters;
	uint32_t						m_refcnt;

};

} /* namespace pss */

#endif /* CONTRIB_CLASSLIB_IMPL_METHODPARAMLISTIMP_H_ */
