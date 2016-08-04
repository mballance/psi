/*
 * InlineExecClosure.h
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
 *  Created on: Jul 22, 2016
 *      Author: ballance
 */

#ifndef IMPL_INLINEEXECIMPL_H_
#define IMPL_INLINEEXECIMPL_H_
#include "api/IBaseItem.h"
#include "api/IInlineExec.h"

using namespace psi_api;

namespace pss {

template <class T> class InlineExecClosure : public psi_api::IInlineExec {
public:

	InlineExecClosure(
			T 				*t,
			void (T::*pre)(psi_api::IObjectContext *ctxt, psshandle_t *hndl),
			void (T::*exec)(),
			void (T::*post)()) : m_target(t), m_pre(pre), m_exec(exec), m_post(post) { }

	virtual ~InlineExecClosure() { }

	virtual void exec(psi_api::IObjectContext *ctxt, psshandle_t *hndl) {
		// Pass the context object on
		((*m_target).*m_pre)(ctxt, hndl);
		// Call the actual exec method
		((*m_target).*m_exec)();
		// Call 'post' to cleanup
		((*m_target).*m_post)();
	}

private:
	T				*m_target;
	void (T::*m_pre)(psi_api::IObjectContext *, psshandle_t *);
	void (T::*m_exec)();
	void (T::*m_post)();
};

}



#endif /* IMPL_INLINEEXECIMPL_H_ */
