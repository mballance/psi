/*
 * ILiteral.h
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
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_ILITERAL_H_
#define SRC_PSI_API_ILITERAL_H_
#include <stdint.h>
#include <string>

#include "api/IExpr.h"

namespace psi_api {

class ILiteral : public IExpr {
public:

	enum LiteralType {
		LiteralInt,
		LiteralBit,
		LiteralBool,
		LiteralString
	};

	virtual ~ILiteral() { }


	virtual LiteralType getLiteralType() const = 0;

	virtual int64_t getInt() const = 0;

	virtual uint64_t getBit() const = 0;

	virtual bool getBool() const = 0;

	virtual const std::string &getString() const = 0;

};

}




#endif /* SRC_PSI_API_ILITERAL_H_ */
