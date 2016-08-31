/*
 * IExecExprStmt.h
 *
 *  Created on: Aug 30, 2016
 *      Author: ballance
 */

#ifndef INCLUDE_API_IEXECEXPRSTMT_H_
#define INCLUDE_API_IEXECEXPRSTMT_H_
#include "api/IExecStmt.h"

namespace psi_api {

class IExecExprStmt : public virtual IExecStmt {
public:

	virtual ~IExecExprStmt() { }

	virtual IExpr *getExpr() = 0;

};

}



#endif /* INCLUDE_API_IEXECEXPRSTMT_H_ */
