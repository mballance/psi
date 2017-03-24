/*
 * action.h
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

#ifndef INCLUDED_ACTION_H
#define INCLUDED_ACTION_H
#include <string>
#include <vector>
#include "scope.h"
#include "prv/action_traversal_activity_stmt.h"
#include "prv/constraint_stmt.h"

// <vendor>
#include "vendor/action_impl.h"
// </vendor>

namespace pss {

class component;

/**
 * User-defined action classes extend from the action base class.
 */
class action : public vendor::action_impl {
public:

	virtual ~action();

	/**
	 * Implements traversal-with
	 */
	prv::action_traversal_activity_stmt with(
			std::initializer_list<prv::constraint_stmt> &constraints
			);

	template <class... T> prv::action_traversal_activity_stmt with(
			const T&... /* prv::constraint_stmt */ items);

protected:

	action(const scope &p);

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

	/**
	 * Solver hook method. Enabled by instantiating an inline exec block
	 * for ExecKind::Body
	 */
	virtual void body();

	/**
	 * Returns a handle to the active component
	 */
	component &comp();


};

} /* namespace pss */

#endif /* INCLUDED_ACTION_H */