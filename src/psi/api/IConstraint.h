/*
 * IConstraint.h
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_ICONSTRAINT_H_
#define SRC_PSI_API_ICONSTRAINT_H_
#include "IBaseItem.h"

namespace psi {

class IConstraint : public IBaseItem {
public:

	enum ConstraintType {
		ConstraintType_Block,
		ConstraintType_Expr,
		ConstraintType_If
	};

public:

	virtual ~IConstraint() { }

	virtual ConstraintType getConstraintType() const = 0;


};

}




#endif /* SRC_PSI_API_ICONSTRAINT_H_ */
