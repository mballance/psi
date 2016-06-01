/*
 * IIntArrayObject.h
 *
 *  Created on: May 31, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IINTARRAYOBJECT_H_
#define SRC_PSI_API_IINTARRAYOBJECT_H_
#include "api/IArrayObject.h"

namespace psi_api {

class IIntArrayObject : public IArrayObject {
public:

	virtual ~IIntArrayObject() { }

	virtual void set(uint32_t idx, uint64_t val) = 0;

	virtual uint64_t get(uint32_t idx) = 0;

};


}



#endif /* SRC_PSI_API_IINTARRAYOBJECT_H_ */
