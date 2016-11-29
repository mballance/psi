/*
 * PSIProcessor.h
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
 *  Created on: Jul 15, 2016
 *      Author: ballance
 */

#ifndef SRC_APPS_PSIVISITOR_H_
#define SRC_APPS_PSIVISITOR_H_
#include "api/IModel.h"
#include "api/IBaseItem.h"
#include <stack>

using namespace psi_api;

namespace psi {
namespace apps {

class PSIVisitor {

public:

	PSIVisitor();

	virtual ~PSIVisitor();

protected:
	virtual void visit_model(IModel *model);

	virtual void visit_package(IPackage *pkg);

	virtual void visit_action(IAction *a);

	virtual void visit_bind(IBind *b);

	virtual void visit_body(IBaseItem *p, const std::vector<IBaseItem *> &items);

	virtual void visit_struct(IStruct *str);

	virtual void visit_component(IComponent *c);

	virtual void visit_comp_pkg_body(const std::vector<IBaseItem *> &items);

	virtual void visit_constraint(IConstraintBlock *c);

	virtual void visit_constraint_stmt(IConstraint *c);

	virtual void visit_constraint_expr_stmt(IConstraintExpr *c);

	virtual void visit_constraint_if_stmt(IConstraintIf *c);

	virtual void visit_constraint_block(IConstraintBlock *block);

	virtual void visit_exec(IExec *e);

	virtual void visit_exec_stmt(IExecStmt *e);

	virtual void visit_exec_call_stmt(IExecCallStmt *s);

	virtual void visit_exec_expr_stmt(IExecExprStmt *s);

	virtual void visit_exec_vendor_stmt(IExecStmt *s);

	virtual void visit_expr(IExpr *e);

	virtual void visit_extend(IExtend *e);

	virtual void visit_binary_expr(IBinaryExpr *be);

	virtual void visit_fieldref_expr(IFieldRef *ref);

	virtual void visit_literal_expr(ILiteral *l);

	virtual void visit_field(IField *f);

	virtual void visit_graph(IGraphStmt *graph);

	virtual void visit_graph_stmt(IGraphStmt *stmt);

	virtual void visit_graph_block_stmt(IGraphBlockStmt *block);

	virtual void visit_graph_repeat_stmt(IGraphRepeatStmt *repeat);

	virtual void visit_graph_select_stmt(IGraphBlockStmt *s);

	virtual void visit_graph_traverse_stmt(IGraphTraverseStmt *t);

	virtual void visit_import_func(IImportFunc *f);

	virtual void visit_vendor_item(IBaseItem *it);

	virtual void remove();

	static std::string type2string(IBaseItem *it);

	static std::string path2string(IFieldRef *f);

	static std::string path2string(const std::vector<IField *> &path);

	void push_scope(IBaseItem *it);

	void pop_scope();

	IBaseItem *scope_parent(IBaseItem *it=0);

	void push_graph(IGraphStmt *it);

	void pop_graph();

	IGraphStmt *graph_parent(IGraphStmt *it=0);

private:
	bool						m_removed;
	std::vector<IBaseItem *>	m_scope_stack;
	std::vector<IGraphStmt *>	m_graph_stack;

};

} /* namespace apps */
} /* namespace psi */

#endif /* SRC_APPS_PSIVISITOR_H_ */
