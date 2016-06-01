/*
 * IArrayObject.h
 *
 *  Created on: May 31, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IARRAYOBJECT_H_
#define SRC_PSI_API_IARRAYOBJECT_H_

#include "api/IArrayObject.h"

namespace psi_api {

class IArrayObject : public IObject {
public:

	virtual ~IArrayObject() { }

	virtual bool isDynamic() = 0;

	virtual uint32_t getSize() = 0;

	virtual void setSize(uint32_t sz) = 0;


};

}




#endif /* SRC_PSI_API_IARRAYOBJECT_H_ */
