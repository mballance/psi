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

	enum ObjectType {
		ObjectType_Object, //! Action or Struct object
		ObjectType_Int,
		ObjectType_Bit,
		ObjectType_Chandle,
		ObjectType_String,
		ObjectType_IntArray,
		ObjectType_BitArray,
		ObjectType_ObjArray
	};

	virtual ~IObject() { }

	virtual ObjectType getObjectType() = 0;

	/**
	 * Returns a sub-field of a composite-type object.
	 */
	virtual IObject *getField(IField *field) = 0;

	int64_t getIntValue() = 0;

	void setIntValue(int64_t v) = 0;

	/**
	 * Returns the bit value
	 */
	uint64_t getBitValue() = 0;

	void setBitValue(uint64_t v) = 0;


};

}


#endif /* SRC_PSI_API_IOBJECT_H_ */
