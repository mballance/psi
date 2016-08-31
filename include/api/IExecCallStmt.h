/*
 * IExecCallStmt.h
 *
 *  Created on: Aug 30, 2016
 *      Author: ballance
 */

#ifndef INCLUDE_API_IEXECCALLSTMT_H_
#define INCLUDE_API_IEXECCALLSTMT_H_
#include "api/IExecStmt.h"

namespace psi_api {

class IExecCallStmt : public virtual IExecStmt {
public:

	virtual ~IExecCallStmt() { }

	/**
	 * The import function
	 */

	virtual IImportFunc *getFunc() = 0;

	virtual std::vector<IExpr *> &getParameters() = 0;
};

}



#endif /* INCLUDE_API_IEXECCALLSTMT_H_ */
