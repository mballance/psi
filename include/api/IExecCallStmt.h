/*
 * IExecCallStmt.h
 *
 * Copyright 2016 Mentor Graphics Corporation
 * All Rights Reserved Worldwide
 *
 * Licensed under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in
 *  compliance with the License.  You may obtain a copy of
 *  the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in
 * writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.  See
 * the License for the specific language governing
 * permissions and limitations under the License.
 * 
 *  Created on: Aug 30, 2016
 *      Author: ballance
 */

#ifndef INCLUDE_API_IEXECCALLSTMT_H_
#define INCLUDE_API_IEXECCALLSTMT_H_
#include "api/IExecStmt.h"

namespace psi_api {

class IExecCallStmt : public virtual IExecStmt {
public:

	virtual ~IExecCallStmt() { }

	/**
	 * The import function
	 */

	virtual IImportFunc *getFunc() = 0;

	virtual std::vector<IExpr *> &getParameters() = 0;
};

}



#endif /* INCLUDE_API_IEXECCALLSTMT_H_ */
