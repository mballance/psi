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

#include "classlib/base_item.h"
#include "classlib/scope.h"
#include "classlib/expr_list.h"

namespace pss {
class attr_item;

/**
 * User-defined action classes extend from the action base class.
 */
class action : public base_item {
public:
	friend class ActionImp;

	virtual ~action();

	expr with(const expr_list &l) const;

	operator attr_item &() const;

#ifdef PSS_HAVE_CXX_11
	template <typename... E> expr with(const E&... rest) {
		return mk_with(expr_list::mklist(rest...));
	}

#endif

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

private:
	// Helper method used by the variadic-template form of with()
	expr mk_with(const expr_list &l) const;

};

} /* namespace pss */

#endif /* INCLUDED_ACTION_H */
