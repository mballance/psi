/*
 * IScalarType.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
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
