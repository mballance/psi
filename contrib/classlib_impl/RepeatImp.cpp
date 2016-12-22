/*
 * repeat.cpp
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

#include "classlib/repeat.h"
#include "ExprCore.h"
#include "ExprImp.h"

namespace pss {

//repeat::repeat(const expr &expr, const expr_list_builder &body) :
//		expr(new ExprCore(expr::GraphRepeat, expr, expr_list(body))) {
//}

repeat::repeat(const expr &cond, const expr_list &body) :
		expr(ExprImp(new ExprCore(ExprImp::GraphRepeat, cond, body))) {
}

repeat::~repeat() { }

expr_list_builder repeat::operator,(const expr &rhs) {
	return expr_list_builder(*this, rhs);
}

expr_list_builder repeat::operator,(const expr_list_builder &rhs) {
	return expr_list_builder(*this, rhs);
}

} /* namespace pss */
