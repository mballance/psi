/*
 * IGraphRepeatStmt.h
 *
 *  Created on: May 8, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IGRAPHREPEATSTMT_H_
#define SRC_PSI_API_IGRAPHREPEATSTMT_H_
#include "api/IExpr.h"
#include "api/IGraphStmt.h"

namespace psi_api {

class IGraphRepeatStmt : public IGraphStmt {
public:

	enum RepeatType {
		RepeatType_Forever,
		RepeatType_While,
		RepeatType_Until
	};
public:


	virtual ~IGraphRepeatStmt() { }

	virtual RepeatType getRepeatType() const = 0;

	virtual IExpr *getCond() = 0;

	virtual IGraphStmt *getBody() = 0;

};
}




#endif /* SRC_PSI_API_IGRAPHREPEATSTMT_H_ */
