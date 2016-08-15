/*
 * IConstraintImplies.h
 *
 *  Created on: Aug 12, 2016
 *      Author: ballance
 */

#ifndef INCLUDE_API_ICONSTRAINTIMPLIES_H_
#define INCLUDE_API_ICONSTRAINTIMPLIES_H_
#include "api/IConstraint.h"
#include "api/IExpr.h"

namespace psi_api {

class IConstraintImplies : public IConstraint {
public:

	virtual ~IConstraintImplies() { }

	virtual IExpr *getCond() const = 0;

	virtual IConstraint *getImp() const = 0;

};

}



#endif /* INCLUDE_API_ICONSTRAINTIMPLIES_H_ */
