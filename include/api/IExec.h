/*
 * IExec.h
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
 *  Created on: Jun 1, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_API_IEXEC_H_
#define SRC_PSI_API_IEXEC_H_
#include <string>
#include "api/IExecCallback.h"
#include "api/IExpr.h"
#include "api/IExecStmt.h"
#include "api/IBaseItem.h"

namespace psi_api {

class IExec :
		public virtual IBaseItem {
public:

	enum ExecKind {
		Declaration,
		Body,
		PreSolve,
		PostSolve
	};

	enum ExecType {
		TargetTemplate,
		Native,
		Inline
	};

public:

	virtual ~IExec() { }

	virtual ExecKind getExecKind() = 0;

	virtual ExecType getExecType() = 0;

	virtual const std::string &getLanguage() const = 0;

	/**
	 * Returns the target-template string for
	 * exec type TargetTemplate
	 */
	virtual const std::string &getTargetTemplate() = 0;

	/**
	 * Returns the inline-exec closure for exec type Inline
	 */
	virtual IExecCallback *getInlineExec() = 0;

	/**
	 * Returns the native-exec statement list
	 */
	virtual const std::vector<IExecStmt *> &getStmts() = 0;

};
}



#endif /* SRC_PSI_API_IEXEC_H_ */
