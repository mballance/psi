/*
 * Expr.h
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
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_EXPR_H
#define INCLUDED_EXPR_H

#include "classlib/Types.h"
#include "classlib/ExprListBuilder.h"

namespace pss {

class ExprListBuilder;
class BaseItem;
class ExprList;
class ConstraintExpr;

#define DECLARE_OP_FUNCTIONS(_prefix, _op) \
	_prefix Expr operator _op (const Expr &lhs, const Expr &rhs); \
	_prefix Expr operator _op (int32_t lhs, const Expr &rhs);     \
	_prefix Expr operator _op (uint32_t lhs, const Expr &rhs);    \


class ExprImp;
class Expr {
public:
	friend ExprImp;

	Expr();

	Expr(uint32_t v);

	Expr(int32_t v);

	Expr(const BaseItem &t);

	Expr(const Expr &rhs);

	Expr(const ExprImp &ptr);

	virtual ~Expr();

	ExprListBuilder operator,(const Expr &rhs);

	Expr operator [] (const Expr &rhs);

	Expr operator [] (int32_t rhs);

	Expr operator [] (uint32_t rhs);

	Expr inside(const ExprList &inside_l);

	Expr implies(const ExprList &inside_l);

#ifdef PSS_HAVE_CXX_11
	template <typename T, typename... R> Expr implies(
			const T		&item,
			const R&...	rest) {
		ExprListBuilder	expr_l;
		_implies(expr_l, item, rest...);
		return implies(ExprList(expr_l));
	}

	template<typename T, typename... R> static void _implies(
			ExprListBuilder 	&expr_l,
			const T 			&i,
			const R&... 		rest) {
		expr_l.add(i);
		_implies(expr_l, rest...);
	}
	static void _implies(ExprListBuilder &el_builder) { }
#endif

//	Expr operator -> (const Expr &rhs);

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
