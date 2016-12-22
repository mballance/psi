/*
 * method_param.h
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

#ifndef INCLUDE_CLASSLIB_METHODPARAM_H_
#define INCLUDE_CLASSLIB_METHODPARAM_H_
#include <string>

namespace pss {

class MethodParamImp;
class method_param_list;
class base_item;
class method_param {
	friend class MethodParamImp;
	friend class method_param_list;
public:
	enum Dir {
		In,
		Out,
		InOut
	};

	virtual ~method_param();

protected:
	method_param(
			const std::string 	&name,
			Dir					dir,
			base_item			*type);

private:
	MethodParamImp				*m_imp;

};

}




#endif /* INCLUDE_CLASSLIB_METHODPARAM_H_ */
