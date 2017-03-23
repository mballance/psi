/*
 * InlineExecIterator.h
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
 *  Created on: Aug 10, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_INLINE_EXEC_ITERATOR_H
#define INCLUDED_INLINE_EXEC_ITERATOR_H
#include <string>
#include "api/IModel.h"

using namespace psi_api;

class InlineExecIterator {
public:
	InlineExecIterator(
			IModel				*model,
			const std::string	&comp_name,
			const std::string	&action_name,
			const std::string	&initial
			);

	virtual ~InlineExecIterator();

	bool traverse();

private:

	enum cb_t {
		PreSolve,
		PostSolve,
		Body
	};

	void traverse(IScopeItem *scope, psshandle_t hndl, cb_t cb);

private:
	IModel						*m_model;
	psshandle_t					m_hndl;
	std::string					m_comp_name;
	std::string					m_action_name;
	std::string					m_initial;

};

#endif /* INCLUDED_INLINE_EXEC_ITERATOR_H */

