/*
 * IFieldRef.h
 *
 *  Created on: May 9, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IFIELDREF_H_
#define SRC_PSI_API_IFIELDREF_H_
#include "api/IExpr.h"

namespace psi_api {

class IField;
class IFieldRef : public IExpr {

public:

	virtual ~IFieldRef() { }

	virtual IField *getField() const = 0;

};


}




#endif /* SRC_PSI_API_IFIELDREF_H_ */
