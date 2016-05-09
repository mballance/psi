/*
 * IGraphBlockStmt.h
 *
 *  Created on: May 8, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IGRAPHBLOCKSTMT_H_
#define SRC_PSI_API_IGRAPHBLOCKSTMT_H_
#include <vector>
#include "api/IGraphStmt.h"

namespace psi_api {

class IGraphBlockStmt : public IGraphStmt {
public:
	virtual ~IGraphBlockStmt() { }

	const std::vector<IGraphStmt *> &getStmts() const;

	void add(IGraphStmt *stmt);

};

}




#endif /* SRC_PSI_API_IGRAPHBLOCKSTMT_H_ */
