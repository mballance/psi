/*
 * IScalarType.h
 *
 *  Created on: May 6, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_ISCALARTYPE_H_
#define SRC_PSI_API_ISCALARTYPE_H_
#include <stdint.h>
#include "api/IBaseItem.h"

namespace psi_api {

class IScalarType : public IBaseItem {

public:
	enum ScalarType {
		ScalarType_Bit,
		ScalarType_Bool,
		ScalarType_Chandle,
		ScalarType_Int,
		ScalarType_String
	};

	virtual ScalarType getScalarType() const = 0;

	/**
	 * Returns the MSB of the type for Bit and Int types
	 */
	virtual uint32_t getMSB() const = 0;

	/**
	 * Returns the LSB of the type for Bit and Int types
	 */
	virtual uint32_t getLSB() const = 0;

};
}




#endif /* SRC_PSI_API_ISCALARTYPE_H_ */
