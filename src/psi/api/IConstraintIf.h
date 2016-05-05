/*
 * IConstraintIf.h
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_ICONSTRAINTIF_H_
#define SRC_PSI_API_ICONSTRAINTIF_H_
#include "IConstraint.h"
#include "IExpr.h"

namespace psi_api {

class IConstraintIf : public IConstraint {
public:

	virtual ~IConstraintIf() { }

	virtual IExpr *getCond() const = 0;

	virtual IConstraint *getTrue() const = 0;

	virtual IConstraint *getFalse() const = 0;

};
}




#endif /* SRC_PSI_API_ICONSTRAINTIF_H_ */
