/*
 * exec_import_call_stmt.h
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

#include "prv/exec_stmt.h"

namespace pss {
class import_func;
namespace prv {

class exec_import_call_stmt : public prv::exec_stmt {
public:

	exec_import_call_stmt();

};

} /* namespace prv */
} /* namespace pss */





#endif /* INCLUDE_CLASSLIB_EXECIMPORTCALLSTMT_H_ */
