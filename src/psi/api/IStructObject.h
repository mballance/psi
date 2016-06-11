/*
 * IStructObject.h
 *
 *  Created on: Jun 1, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_ISTRUCTOBJECT_H_
#define SRC_PSI_API_ISTRUCTOBJECT_H_

namespace psi_api {

class IStructObject : public IObject {
public:

	virtual ~IStructObject() { }

	virtual IStruct *getStruct() const = 0;

	/**
	 * Returns the object representation of a
	 * field of this struct.
	 */
	virtual IObject *getField(IField *field) = 0;


};

}




#endif /* SRC_PSI_API_ISTRUCTOBJECT_H_ */
