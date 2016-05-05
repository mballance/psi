/*
 * IExpr.h
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IEXPR_H_
#define SRC_PSI_API_IEXPR_H_

namespace psi_api {

class IExpr {
public:
	enum ExprType {
		ExprType_Literal,
		ExprType_BinOp,
		ExprType_TypeRef
	};

public:

	virtual ~IExpr() { }

	virtual ExprType getType() const = 0;


};

}



#endif /* SRC_PSI_API_IEXPR_H_ */
