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

#include "classlib/pss_types.h"
#include "classlib/expr_list_builder.h"

namespace pss {

class expr_list_builder;
class base_item;
class expr_list;
class ConstraintExpr;

#define DECLARE_OP_FUNCTIONS(_prefix, _op) \
	_prefix expr operator _op (const expr &lhs, const expr &rhs); \
	_prefix expr operator _op (int32_t lhs, const expr &rhs);     \
	_prefix expr operator _op (uint32_t lhs, const expr &rhs);    \


class ExprImp;
class expr {
public:
	friend ExprImp;

	expr();

	expr(uint32_t v);

	expr(int32_t v);

	expr(const base_item &t);

	expr(const expr &rhs);

	expr(const ExprImp &ptr);

	virtual ~expr();

	expr_list_builder operator,(const expr &rhs);

	expr operator [] (const expr &rhs);

	expr operator [] (int32_t rhs);

	expr operator [] (uint32_t rhs);

	expr inside(const expr_list &inside_l);

	expr implies(const expr_list &inside_l);

#ifdef PSS_HAVE_CXX_11
	template <typename T, typename... R> expr implies(
			const T		&item,
			const R&...	rest) {
		expr_list_builder	expr_l;
		_implies(expr_l, item, rest...);
		return implies(expr_list(expr_l));
	}

	template<typename T, typename... R> static void _implies(
			expr_list_builder 	&expr_l,
			const T 			&i,
			const R&... 		rest) {
		expr_l.add(i);
		_implies(expr_l, rest...);
	}
	static void _implies(expr_list_builder &el_builder) { }
#endif

//	expr operator -> (const expr &rhs);

	DECLARE_OP_FUNCTIONS(friend, ==)
	DECLARE_OP_FUNCTIONS(friend, !=)
	DECLARE_OP_FUNCTIONS(friend, <=)
	DECLARE_OP_FUNCTIONS(friend, <)
	DECLARE_OP_FUNCTIONS(friend, >=)
	DECLARE_OP_FUNCTIONS(friend, >)
	DECLARE_OP_FUNCTIONS(friend, &)
	DECLARE_OP_FUNCTIONS(friend, &&)
	DECLARE_OP_FUNCTIONS(friend, |)
	DECLARE_OP_FUNCTIONS(friend, ||)
	DECLARE_OP_FUNCTIONS(friend, -)
	DECLARE_OP_FUNCTIONS(friend, +)
	DECLARE_OP_FUNCTIONS(friend, *)
	DECLARE_OP_FUNCTIONS(friend, /)
	DECLARE_OP_FUNCTIONS(friend, %)

	const ExprImp &imp() const;

protected:
	ExprImp					*m_core;

};

DECLARE_OP_FUNCTIONS( , ==)
DECLARE_OP_FUNCTIONS( , !=)
DECLARE_OP_FUNCTIONS( , <=)
DECLARE_OP_FUNCTIONS( , <)
DECLARE_OP_FUNCTIONS( , >=)
DECLARE_OP_FUNCTIONS( , >)
DECLARE_OP_FUNCTIONS( , &)
DECLARE_OP_FUNCTIONS( , &&)
DECLARE_OP_FUNCTIONS( , |)
DECLARE_OP_FUNCTIONS( , ||)
DECLARE_OP_FUNCTIONS( , -)
DECLARE_OP_FUNCTIONS( , +)
DECLARE_OP_FUNCTIONS( , *)
DECLARE_OP_FUNCTIONS( , /)
DECLARE_OP_FUNCTIONS( , %)

#undef DECLARE_OP_FUNCTIONS


} /* namespace pss */

#endif /* INCLUDED_EXPR_H */
