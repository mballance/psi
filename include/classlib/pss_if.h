/*
 * pss_if.h
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
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_CLASSLIB_IF_H_
#define SRC_PSI_CLASSLIB_IF_H_

#include "classlib/expr.h"
#include "classlib/expr_list.h"

namespace pss {

class pss_if : public expr {
public:
	pss_if(const expr &cond, const expr_list &true_expr);

	pss_if(const expr &cond, const expr_list &true_expr, const expr_list &false_expr);

	virtual ~pss_if();

};

} /* namespace pss */

#endif /* SRC_PSI_CLASSLIB_IF_H_ */
