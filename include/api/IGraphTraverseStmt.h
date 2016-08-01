/*
 * IGraphTraverseStmt.h
 *
 *  Created on: Jun 10, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IGRAPHTRAVERSESTMT_H_
#define SRC_PSI_API_IGRAPHTRAVERSESTMT_H_
#include "api/IGraphStmt.h"
#include "api/IFieldRef.h"
#include "api/IConstraint.h"

namespace psi_api {

class IGraphTraverseStmt : public IGraphStmt {
public:

	virtual ~IGraphTraverseStmt() { }

	virtual IFieldRef *getAction() const = 0;

	virtual IConstraint *getWith() const = 0;

};

}




#endif /* SRC_PSI_API_IGRAPHTRAVERSESTMT_H_ */
