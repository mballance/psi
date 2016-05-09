/*
 * IBinaryExpr.h
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IBINARYEXPR_H_
#define SRC_PSI_API_IBINARYEXPR_H_

#include "api/IExpr.h"

namespace psi_api {

class IBinaryExpr : public IExpr {

public:

	enum BinOpType {
		BinOp_Eq,
		BinOp_EqEq,
		BinOp_NotEq,
		BinOp_GE,
		BinOp_GT,
		BinOp_LE,
		BinOp_LT,
		BinOp_And,
		BinOp_AndAnd,
		BinOp_Or,
		BinOp_OrOr,
		BinOp_Minus,
		BinOp_Plus,
		BinOp_Multiply,
		BinOp_Divide,
		BinOp_Mod,
		BinOp_ArrayRef
	};

public:

	virtual ~IBinaryExpr() { }

	virtual BinOpType getBinOpType() const = 0;

	virtual IExpr *getLHS() const = 0;

	virtual IExpr *getRHS() const = 0;

};
}




#endif /* SRC_PSI_API_IBINARYEXPR_H_ */
