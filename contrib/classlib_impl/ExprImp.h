/*
 * ExprImp.h
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
 *  Created on: Jul 27, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_EXPR_IMP_H
#define INCLUDED_EXPR_IMP_H

#include "../../include/prv/expr.h"
#include "SharedPtr.h"

namespace pss {

class ExprCore;
class ExprImp : public SharedPtr<ExprCore> {
public:
	enum Operator {
		LiteralUint,
		LiteralInt,
		LiteralBit,
		LiteralBool,
		LiteralString,

		BinOp_Eq,
		BinOp_EqEq,
		BinOp_NotEq,
		BinOp_GE,
		BinOp_GT,
		BinOp_LE, // 10
		BinOp_LT,
		BinOp_And,
		BinOp_AndAnd,
		BinOp_Or,
		BinOp_OrOr,
		BinOp_Minus,
		BinOp_Plus,
		BinOp_Multiply,
		BinOp_Divide,
		BinOp_Mod, // 20
		BinOp_ArrayRef,
		BinOp_Inside,

		Stmt_If,
		Stmt_IfElse,
		Stmt_Implies,

		GraphParallel,
		GraphRepeat,
		GraphSchedule,
		GraphSelect,
		GraphWith, // 30

		ImportCall,

		List,
		TypeRef
	};

public:

	ExprImp();

	ExprImp(ExprCore *p);

	ExprImp(const ExprImp &p);

	ExprImp(const expr &p);

	virtual ~ExprImp();

	static const char *toString(Operator op);

	static bool isBinOp(Operator op);

	Operator getOp() const;

};

}




#endif /* CONTRIB_CLASSLIB_IMPL_EXPRIMP_H_ */
