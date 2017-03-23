/*
 * expr.h
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
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_EXPR_H
#define INCLUDED_EXPR_H
#include <stdint.h>

namespace pss {
namespace prv {

class expr_list_builder;
class base_item;
class expr_list;
class ConstraintExpr;

class expr : public vendor::expr_impl {
public:

	expr();

	expr(uint32_t v);

	expr(int32_t v);

#ifdef UNDEFINED
	expr(const base_item &t);
#endif

	expr(const expr &rhs);

	virtual ~expr();

#ifdef UNDEFINED
	expr_list_builder operator,(const expr &rhs);

	expr operator [] (const expr &rhs);

	expr operator [] (int32_t rhs);

	expr operator [] (uint32_t rhs);

	expr inside(const expr_list &inside_l);

	expr implies(const expr_list &inside_l);
#endif

	template <typename T, typename... R> expr implies(
			const T		&item,
			const R&...	rest);

	expr operator == (const expr &rhs);
	expr operator != (const expr &rhs);
	expr operator <= (const expr &rhs);
	expr operator <  (const expr &rhs);
	expr operator >= (const expr &rhs);
	expr operator >  (const expr &rhs);
	expr operator &  (const expr &rhs);
	expr operator && (const expr &rhs);
	expr operator |  (const expr &rhs);
	expr operator || (const expr &rhs);
	expr operator -  (const expr &rhs);
	expr operator +  (const expr &rhs);
	expr operator *  (const expr &rhs);
	expr operator /  (const expr &rhs);
	expr operator %  (const expr &rhs);

};


} /* namespace prv */
} /* namespace pss */

#endif /* INCLUDED_EXPR_H */
