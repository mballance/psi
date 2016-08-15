/*
 * IExecStmt.h
 *
 *  Created on: Aug 12, 2016
 *      Author: ballance
 */

#ifndef INCLUDE_API_IEXECSTMT_H_
#define INCLUDE_API_IEXECSTMT_H_
#include <vector>
#include "api/IExpr.h"
#include "api/IImportFunc.h"

namespace psi_api {

class IExecStmt {
public:

	virtual ~IExecStmt() { }

	virtual IExpr *getExpr() = 0;

	virtual IImportFunc *getFunc() = 0;

	virtual std::vector<IExpr *> &getCallParams() = 0;

};

}



#endif /* INCLUDE_API_IEXECSTMT_H_ */
