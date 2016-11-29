/*
 * ExecImportCallStmt.h
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
 *  Created on: Aug 29, 2016
 *      Author: ballance
 */

#ifndef INCLUDE_CLASSLIB_EXECIMPORTCALLSTMT_H_
#define INCLUDE_CLASSLIB_EXECIMPORTCALLSTMT_H_

#include "classlib/ExecStmt.h"
#include "classlib/ExprList.h"

namespace pss {

class ImportFunc;
class ExecImportCallStmt : public ExecStmt {
public:
	friend ImportFunc;

private:
	ExecImportCallStmt(const ImportFunc &f, const ExprList &plist);

};

}




#endif /* INCLUDE_CLASSLIB_EXECIMPORTCALLSTMT_H_ */
