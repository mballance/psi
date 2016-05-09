/*
 * IGraphStmt.h
 *
 *  Created on: May 8, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IGRAPHSTMT_H_
#define SRC_PSI_API_IGRAPHSTMT_H_

namespace psi_api {

class IGraphStmt {
public:
	enum GraphStmtType {
		GraphStmt_Block,
		GraphStmt_IfElse,
		GraphStmt_Parallel,
		GraphStmt_Schedule,
		GraphStmt_Select,
		GraphStmt_Repeat
	};

public:
	virtual ~IGraphStmt() { }

	virtual GraphStmtType getStmtType() const = 0;

};
}




#endif /* SRC_PSI_API_IGRAPHSTMT_H_ */
