/*
 * ExprImp.h
 *
 *  Created on: Jul 27, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_EXPR_IMP_H
#define INCLUDED_EXPR_IMP_H

#include "classlib/Expr.h"
#include "SharedPtr.h"

namespace psi {

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

		Stmt_If,
		Stmt_IfElse,

		GraphParallel,
		GraphRepeat, // 25
		GraphSchedule,
		GraphSelect,
		GraphWith,

		ImportCall,

		List, // 30
		TypeRef
	};

public:
	ExprImp(ExprCore *p) : SharedPtr<ExprCore>(p)  { }

	ExprImp(const ExprImp &p) : SharedPtr<ExprCore>(p)  { }

	virtual ~ExprImp() { }

};

}




#endif /* CONTRIB_CLASSLIB_IMPL_EXPRIMP_H_ */
