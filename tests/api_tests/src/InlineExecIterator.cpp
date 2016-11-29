/*
 * InlineExecIterator.cpp
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

#include "InlineExecIterator.h"
#include "TestCallbackContextImpl.h"

InlineExecIterator::InlineExecIterator(
		IModel				*model,
		const std::string	&comp_name,
		const std::string	&action_name,
		const std::string	&initial) {
	m_model = model;
	m_comp_name = comp_name;
	m_action_name = action_name;
	m_initial = initial;
}

InlineExecIterator::~InlineExecIterator() {
	// TODO Auto-generated destructor stub
}

bool InlineExecIterator::traverse() {
	TestCallbackContextImpl *ctxt = dynamic_cast<TestCallbackContextImpl *>(m_model->getCallbackContext());

	if (!ctxt) {
		fprintf(stdout, "Error: CallbackContext is not TestCallbackContextImpl\n");
		return false;
	}

	IComponent *c = 0;
	IAction *a = 0;

	for (std::vector<IBaseItem *>::const_iterator it=m_model->getItems().begin();
			it!=m_model->getItems().end(); it++) {
		if ((*it)->getType() == IBaseItem::TypeComponent &&
				dynamic_cast<IComponent *>(*it)->getName() == m_comp_name) {
			c = dynamic_cast<IComponent *>(*it);
			break;
		}
	}

	if (!c) {
		fprintf(stdout, "Error: call_inline_exec - failed to find component %s\n",
				m_comp_name.c_str());
		return false;
	}

	for (std::vector<IBaseItem *>::const_iterator it=c->getItems().begin();
			it!=c->getItems().end(); it++) {
		if ((*it)->getType() == IBaseItem::TypeAction &&
				dynamic_cast<IAction *>(*it)->getName() == m_action_name) {
			a = dynamic_cast<IAction *>(*it);
			break;
		}
	}

	if (!a) {
		fprintf(stdout, "Error: call_inline_exec - failed to find action %s\n",
				m_action_name.c_str());
		return false;
	}

	ctxt->init(m_initial, m_model, c);

	// Now, traverse through the action hierarchy
	// - Call pre_solve
	// - Call post_solve
	// - Call body
	psshandle_t hndl = ctxt->getActionNode();
	traverse(a, hndl, PreSolve);
	traverse(a, hndl, PostSolve);
	traverse(a, hndl, Body);

}

void InlineExecIterator::traverse(IScopeItem *scope, psshandle_t hndl, cb_t cb) {
	IExecCallback *exec_cb = 0;

	// Figure out whether there's a matching exec
	for (std::vector<IBaseItem *>::const_iterator it=scope->getItems().begin();
			it!=scope->getItems().end(); it++) {
		if ((*it)->getType() == IBaseItem::TypeExec) {
			IExec *exec = dynamic_cast<IExec *>(*it);
			switch (cb) {
			case PreSolve: {
				if (exec->getExecKind() == IExec::PreSolve) {
					exec_cb = exec->getInlineExec();
				}
			} break;
			case PostSolve: {
				if (exec->getExecKind() == IExec::PostSolve) {
					exec_cb = exec->getInlineExec();
				}
			} break;
			case Body: {
				if (exec->getExecKind() == IExec::Body) {
					exec_cb = exec->getInlineExec();
				}
			} break;
			}
		}
	}

	if (exec_cb) {
		exec_cb->exec(m_model, hndl);
	}
}

