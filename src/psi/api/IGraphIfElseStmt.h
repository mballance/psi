/*
 * IGraphIfElseStmt.h
 *
 *  Created on: May 8, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IGRAPHIFELSESTMT_H_
#define SRC_PSI_API_IGRAPHIFELSESTMT_H_
#include "api/IExpr.h"
#include "api/IGraphStmt.h"

namespace psi_api {

class IGraphIfElseStmt : public IGraphStmt {

public:

	virtual ~IGraphIfElseStmt() { }

	virtual IExpr *getCond() = 0;

	virtual IGraphStmt *getTrue() = 0;

	virtual IGraphStmt *getFalse() = 0;

};
}




#endif /* SRC_PSI_API_IGRAPHIFELSESTMT_H_ */
