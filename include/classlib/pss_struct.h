/*
 * pss_struct.h
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
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_STRUCT_H
#define INCLUDED_STRUCT_H
#include <string>

#include "classlib/base_item.h"
#include "classlib/scope.h"

namespace pss {

class attr_item;

class pss_struct : public base_item {

public:

		virtual ~pss_struct();

		operator expr() const;

		operator attr_item &() const;

	protected:

		pss_struct(const scope &p);

		pss_struct(BaseItemImp *imp);

		/**
		 * Solver hook method. Enabled by instantiating an inline exec block
		 * for ExecKind::PreSolve
		 */
		virtual void pre_solve();

		/**
		 * Solver hook method. Enabled by instantiating an inline exec block
		 * for ExecKind::PostSolve
		 */
		virtual void post_solve();

};

} /* namespace pss */

#endif /* STRUCT_H_ */
