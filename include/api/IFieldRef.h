/*
 * IFieldRef.h
 *
 *  Created on: May 9, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IFIELDREF_H_
#define SRC_PSI_API_IFIELDREF_H_
#include <vector>
#include "api/IExpr.h"

namespace psi_api {

class IField;
class IFieldRef : public IExpr {

public:

	virtual ~IFieldRef() { }

	/**
	 * Returns a list of field refs that form the field-reference expression
	 * a.b.c, for example, where a is a field of type A, b is a field of type B, etc
	 * would be as follows:
	 * { a-field declared within type A, b-field declared within type B, etc }
	 */
	virtual const std::vector<IField * > &getFieldPath() const = 0;

};


}




#endif /* SRC_PSI_API_IFIELDREF_H_ */
