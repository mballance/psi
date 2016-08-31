/*
 * IExecExprStmt.h
 *
 *  Created on: Aug 30, 2016
 *      Author: ballance
 */

#ifndef INCLUDE_API_IEXECEXPRSTMT_H_
#define INCLUDE_API_IEXECEXPRSTMT_H_

namespace psi_api {

class IExecExprStmt {
public:

	virtual ~IExecExprStmt() { }

	virtual IExpr *getExpr() = 0;

};

}



#endif /* INCLUDE_API_IEXECEXPRSTMT_H_ */
