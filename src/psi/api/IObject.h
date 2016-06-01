/*
 * IObject.h
 *
 *  Created on: May 30, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IOBJECT_H_
#define SRC_PSI_API_IOBJECT_H_
#include "api/IBaseItem.h"

namespace psi_api {

class IObject : public IBaseItem {
public:

	virtual ~IObject() { }

	/**
	 * Returns the declaration type of this object, such
	 * as IAction, IStruct, IScalarType
	 */
	virtual IBaseItem *getTypeDeclaration() = 0;

};

}


#endif /* SRC_PSI_API_IOBJECT_H_ */
