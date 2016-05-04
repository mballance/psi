/*
 * IConstraintBlock.h
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_ICONSTRAINTBLOCK_H_
#define SRC_PSI_API_ICONSTRAINTBLOCK_H_
#include <vector>
#include <string>

#include "IConstraint.h"

namespace psi {

class IConstraintBlock : public IConstraint {

public:

	virtual ~IConstraintBlock() { }

	virtual const std::string &getName() const = 0;

	virtual void add(IConstraint *c) = 0;

	virtual const std::vector<IConstraint *> &getConstraints() const = 0;

};
}




#endif /* SRC_PSI_API_ICONSTRAINTBLOCK_H_ */
