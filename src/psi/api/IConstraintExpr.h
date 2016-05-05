/*
 * IConstraintExpr.h
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_ICONSTRAINTEXPR_H_
#define SRC_PSI_API_ICONSTRAINTEXPR_H_
#include "api/IConstraint.h"
#include "api/IExpr.h"

namespace psi_api {

class IConstraintExpr : public IConstraint {

public:

	virtual ~IConstraintExpr() { }

	virtual IExpr *getExpr() const = 0;

};
}



#endif /* SRC_PSI_API_ICONSTRAINTEXPR_H_ */
