/*
 * Action.h
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
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef ACTION_H_
#define ACTION_H_
#include <string>

#include "classlib/NamedBaseItem.h"
#include "classlib/Scope.h"
#include "classlib/TypePath.h"

namespace psi_api {
	class IObjectContext;
	class IBaseItem;
	struct psshandle_t;
}

using namespace psi_api;

namespace psi {

class Elaborator;
class Action : public NamedBaseItem {
friend Elaborator;
public:

		Action(const Scope &p);

		virtual ~Action();

		const TypePath &getSuperType() const { return m_super_type; }

	protected:

		/**
		 * Solver hook method. Enabled by instantiating an inline Exec block
		 * for ExecKind::PreSolve
		 */
		virtual void pre_solve();

		/**
		 * Solver hook method. Enabled by instantiating an inline Exec block
		 * for ExecKind::PostSolve
		 */
		virtual void post_solve();

		/**
		 * Solver hook method. Enabled by instantiating an inline Exec block
		 * for ExecKind::Body
		 */
		virtual void body();

	private:

		virtual void inline_exec_pre(IObjectContext *ctxt, psshandle_t *hndl);

		virtual void inline_exec_post();


	private:
		TypePath							m_super_type;
		IObjectContext						*m_ctxt;
		psshandle_t							*m_hndl;

};

} /* namespace psi */

#endif /* ACTION_H_ */
