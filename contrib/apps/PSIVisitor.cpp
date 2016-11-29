/*
 * PSIProcessor.cpp
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

#include "PSIVisitor.h"
#include "PSIUtil.h"
#include "api_impl/ModelImpl.h"
#include <stdio.h>

using namespace psi;

namespace psi {
namespace apps {

PSIVisitor::PSIVisitor() : m_removed(false) {
	// TODO Auto-generated constructor stub

}

PSIVisitor::~PSIVisitor() {
	// TODO Auto-generated destructor stub
}

void PSIVisitor::visit_model(IModel *model) {
	fprintf(stdout, "--> visit_model(%p)\n", model);
	IPackage *pkg = model->getGlobalPackage();
	visit_package(pkg);

	ModelImpl *model_i = dynamic_cast<ModelImpl *>(model);
	for (int32_t i=0; i<model->getItems().size(); i++) {
		IBaseItem *it = model->getItems().at(i);
		fprintf(stdout, "-- it=%p %d\n", it, it->getType());

		m_removed = false;
		push_scope(it);
		if (it->getType() == IBaseItem::TypePackage) {
			IPackage *pkg = dynamic_cast<IPackage *>(it);
			visit_package(pkg);
		} else if (it->getType() == IBaseItem::TypeComponent) {
			visit_component(dynamic_cast<IComponent *>(it));
		} else {
			// Really shouldn't be anything else in the global scope
		}
		pop_scope();

		if (m_removed) {
			model_i->remove(it);
			delete it;
			i--;
		}
	}
	fprintf(stdout, "<-- visit_model(%p)\n", model);
}

void PSIVisitor::visit_package(IPackage *pkg) {
	std::vector<IBaseItem *>::const_iterator it=pkg->getItems().begin();

	for (int32_t i=0; i<pkg->getItems().size(); i++) {
		IBaseItem *it = pkg->getItems().at(i);

		push_scope(it);
		m_removed = false;
		switch (it->getType()) {
			case IBaseItem::TypeAction:
				// TODO:
				break;

			case IBaseItem::TypeStruct:
				visit_struct(dynamic_cast<IStruct *>(it));
				break;

			case IBaseItem::TypeExtend:
				visit_extend(dynamic_cast<IExtend *>(it));
				break;

			case IBaseItem::TypeImportFunc:
				visit_import_func(dynamic_cast<IImportFunc *>(it));
				break;

			default:
				fprintf(stdout, "Error: Unhandled package item: %d\n", it->getType());
		}
		pop_scope();

		if (m_removed) {
			dynamic_cast<PackageImpl *>(pkg)->remove(it);
			delete it;
		}
	}

	m_removed = false;
}

void PSIVisitor::visit_action(IAction *a) {

	fprintf(stdout, "--> visit_action\n");
	fflush(stdout);

	visit_body(a, a->getItems());

	fprintf(stdout, "graph=%p\n", a->getGraph());
	if (a->getGraph()) {
		visit_graph(a->getGraph());
	}

	fprintf(stdout, "<-- visit_action\n");
	fflush(stdout);
	m_removed = false;
}

void PSIVisitor::visit_bind(IBind *b) {

}

void PSIVisitor::visit_body(IBaseItem *p, const std::vector<IBaseItem *> &items) {
	std::vector<IBaseItem *>::const_iterator it = items.begin();

	for (int32_t i=0; i<items.size(); i++) {
		IBaseItem *it = items.at(i);
		m_removed = false;

		switch (it->getType()) {
		case IBaseItem::TypeBind:
			visit_bind(dynamic_cast<IBind *>(it));
			break;
		case IBaseItem::TypeConstraint:
			visit_constraint(dynamic_cast<IConstraintBlock *>(it));
			break;

		case IBaseItem::TypeField:
			visit_field(dynamic_cast<IField *>(it));
			break;

		case IBaseItem::TypeExec:
			visit_exec(dynamic_cast<IExec *>(it));
			break;

		case IBaseItem::TypeVendor:
			visit_vendor_item(it);
			break;

		default:
			fprintf(stdout, "Error: Unknown body item %d\n", it->getType());
		}

		if (m_removed) {
			ScopeItemImpl *s = dynamic_cast<ScopeItemImpl *>(p);
			s->remove(it);
			delete it;
		}
	}

	m_removed = false;
}

void PSIVisitor::visit_struct(IStruct *str) {
	m_removed = false;

	visit_body(str, str->getItems());

	m_removed = false;
}

void PSIVisitor::visit_component(IComponent *c) {

	fprintf(stdout, "--> visit_component\n");
	fflush(stdout);

	visit_comp_pkg_body(c->getItems());

	fprintf(stdout, "<-- visit_component\n");
	fflush(stdout);
}

void PSIVisitor::visit_comp_pkg_body(const std::vector<IBaseItem *> &items) {
	std::vector<IBaseItem *>::const_iterator it=items.begin();

	for (; it!=items.end(); it++) {
		fprintf(stdout, " -- item %p %d\n", *it, (*it)->getType());
		fflush(stdout);

		push_scope(*it);
		switch ((*it)->getType()) {
			case IBaseItem::TypeAction:
				fprintf(stdout, "---> visit_action\n");
				fflush(stdout);
				visit_action(dynamic_cast<IAction *>(*it));
				fprintf(stdout, "<--- visit_action\n");
				fflush(stdout);
				break;

			case IBaseItem::TypeStruct:
				visit_struct(dynamic_cast<IStruct *>(*it));
				break;
		}
		pop_scope();
	}
}

void PSIVisitor::visit_constraint(IConstraintBlock *c) {
	for (std::vector<IConstraint *>::const_iterator it=c->getConstraints().begin();
			it!=c->getConstraints().end(); it++) {
		visit_constraint_stmt(*it);
	}
}

void PSIVisitor::visit_constraint_stmt(IConstraint *c) {
	switch (c->getConstraintType()) {
	case IConstraint::ConstraintType_Block: {

		visit_constraint_block(dynamic_cast<IConstraintBlock *>(c));
	} break;

	case IConstraint::ConstraintType_Expr:
		visit_constraint_expr_stmt(dynamic_cast<IConstraintExpr *>(c));
		break;

	case IConstraint::ConstraintType_If:
		visit_constraint_if_stmt(dynamic_cast<IConstraintIf *>(c));
		break;
	}
}

void PSIVisitor::visit_constraint_expr_stmt(IConstraintExpr *c) {
	visit_expr(c->getExpr());
}

void PSIVisitor::visit_constraint_if_stmt(IConstraintIf *c) {
	visit_expr(c->getCond());

	visit_constraint_stmt(c->getTrue());

	if (c->getFalse()) {
		visit_constraint_stmt(c->getFalse());
	}
}

void PSIVisitor::visit_constraint_block(IConstraintBlock *block) {
	std::vector<IConstraint *>::const_iterator it = block->getConstraints().begin();

	for (; it!=block->getConstraints().end(); it++) {
		IConstraint *c = *it;
		visit_constraint_stmt(c);
	}
}

void PSIVisitor::visit_exec(IExec *e) {
	for (std::vector<IExecStmt *>::const_iterator it=e->getStmts().begin();
			it!=e->getStmts().end(); it++) {
		visit_exec_stmt(*it);
	}
}

void PSIVisitor::visit_exec_stmt(IExecStmt *e) {
	switch (e->getStmtType()) {
	case IExecStmt::StmtType_Call:
		visit_exec_call_stmt(dynamic_cast<IExecCallStmt *>(e));
		break;

	case IExecStmt::StmtType_Expr:
		visit_exec_expr_stmt(dynamic_cast<IExecExprStmt *>(e));
		break;

	case IExecStmt::StmtType_Vendor:
		visit_exec_vendor_stmt(e);
		break;
	}
}

void PSIVisitor::visit_exec_call_stmt(IExecCallStmt *s) {
	// NOP
}

void PSIVisitor::visit_exec_expr_stmt(IExecExprStmt *s) {
	// NOP
}

void PSIVisitor::visit_exec_vendor_stmt(IExecStmt *s) {
	// NOP
}

void PSIVisitor::visit_expr(IExpr *e) {
	if (!e) {
		fprintf(stdout, "Error: null expression\n");
		return;
	}
	switch (e->getType()) {
		case IExpr::ExprType_BinOp: visit_binary_expr(dynamic_cast<IBinaryExpr *>(e)); break;
		case IExpr::ExprType_FieldRef: visit_fieldref_expr(dynamic_cast<IFieldRef *>(e)); break;
		case IExpr::ExprType_Literal: visit_literal_expr(dynamic_cast<ILiteral *>(e)); break;
	}
}

void PSIVisitor::visit_extend(IExtend *e) {
	visit_body(e, e->getItems());
}

void PSIVisitor::visit_binary_expr(IBinaryExpr *be) {
	visit_expr(be->getLHS());
	visit_expr(be->getRHS());
}

void PSIVisitor::visit_fieldref_expr(IFieldRef *ref) {

}

void PSIVisitor::visit_literal_expr(ILiteral *l) {

}


void PSIVisitor::visit_field(IField *f) {

}

void PSIVisitor::visit_graph(IGraphStmt *graph) {
	fprintf(stdout, "visit_graph: %d\n", graph->getStmtType());
	fflush(stdout);
	if (graph->getStmtType() == IGraphStmt::GraphStmt_Block) {
		IGraphBlockStmt *b = dynamic_cast<IGraphBlockStmt *>(graph);
		push_graph(b);
		for (std::vector<IGraphStmt *>::const_iterator it=b->getStmts().begin();
				it!=b->getStmts().end(); it++) {
			visit_graph_stmt(*it);
		}
		pop_graph();
	} else {
		visit_graph_stmt(graph);
	}
}

void PSIVisitor::visit_graph_stmt(IGraphStmt *stmt) {
	fprintf(stdout, "visit_graph_stmt: %d\n", stmt->getStmtType());
	fflush(stdout);

	push_graph(stmt);

	switch (stmt->getStmtType()) {
	case IGraphStmt::GraphStmt_Block: {
		visit_graph_block_stmt(dynamic_cast<IGraphBlockStmt *>(stmt));
	} break;

	case IGraphStmt::GraphStmt_IfElse: {
		fprintf(stdout, "TODO: GraphStmt_IfElse\n");
	} break;

	case IGraphStmt::GraphStmt_Parallel: {
		visit_graph_block_stmt(dynamic_cast<IGraphBlockStmt *>(stmt));
	} break;

	case IGraphStmt::GraphStmt_Schedule: {
		visit_graph_block_stmt(dynamic_cast<IGraphBlockStmt *>(stmt));
	} break;

	case IGraphStmt::GraphStmt_Select: {
		visit_graph_select_stmt(dynamic_cast<IGraphBlockStmt *>(stmt));
	} break;

	case IGraphStmt::GraphStmt_Repeat: {
		visit_graph_repeat_stmt(dynamic_cast<IGraphRepeatStmt *>(stmt));
	} break;

	case IGraphStmt::GraphStmt_Traverse: {
		visit_graph_traverse_stmt(dynamic_cast<IGraphTraverseStmt *>(stmt));
	} break;

	default: fprintf(stdout, "TODO: handle graph stmt %d\n", stmt->getStmtType());

	}

	pop_graph();
}

void PSIVisitor::visit_graph_repeat_stmt(IGraphRepeatStmt *repeat) {
	visit_graph_stmt(repeat->getBody());
}

void PSIVisitor::visit_graph_select_stmt(IGraphBlockStmt *s) {
	visit_graph_block_stmt(s);
}

void PSIVisitor::visit_graph_traverse_stmt(IGraphTraverseStmt *t) {
	if (t->getWith()) {
		visit_constraint_stmt(t->getWith());
	}
}

void PSIVisitor::visit_import_func(IImportFunc *f) {
	// NOP
}

void PSIVisitor::visit_vendor_item(IBaseItem *it) {

}

void PSIVisitor::visit_graph_block_stmt(IGraphBlockStmt *block) {
	std::vector<IGraphStmt *>::const_iterator it;

	for (it=block->getStmts().begin(); it!=block->getStmts().end(); it++) {
		visit_graph_stmt(*it);
	}
}

void PSIVisitor::remove() {
	m_removed = true;
}

std::string PSIVisitor::type2string(IBaseItem *it) {
	std::string ret;

	while (it) {
		INamedItem *ni = PSIUtil::toNamedItem(it);

		if (ni) {
			if (ret.size() > 0) {
				ret.insert(0, "::");
			}
			ret.insert(0, ni->getName());
		} else {
			break;
		}

		it = it->getParent();
	}

	return ret;
}

std::string PSIVisitor::path2string(IFieldRef *f) {
	std::string ret;
	std::vector<IField *>::const_iterator it;

	for (it=f->getFieldPath().begin(); it!=f->getFieldPath().end(); ) {
		IField *field = *(it);
		ret += field->getName();
		it++;
		if (it != f->getFieldPath().end()) {
			ret += ".";
		}
	}

	return ret;
}

std::string PSIVisitor::path2string(const std::vector<IField *> &path) {
	std::string ret;
	std::vector<IField *>::const_iterator it;

	for (it=path.begin(); it!=path.end(); ) {
		IField *field = *(it);
		ret += field->getName();
		it++;
		if (it != path.end()) {
			ret += ".";
		}
	}

	return ret;
}

void PSIVisitor::push_scope(IBaseItem *it) {
	m_scope_stack.push_back(it);
}

void PSIVisitor::pop_scope() {
	if (m_scope_stack.size() > 0) {
		m_scope_stack.pop_back();
	}
}

IBaseItem *PSIVisitor::scope_parent(IBaseItem *it) {
	if (it) {
		for (int32_t i=m_scope_stack.size(); i>=0; i--) {
			if (m_scope_stack.at(i) == it && i>0) {
				return m_scope_stack.at(i-1);
			}
		}
	} else {
		if (m_scope_stack.size() > 0) {
			return m_scope_stack.at(m_scope_stack.size()-1);
		}
	}
	return 0;
}

void PSIVisitor::push_graph(IGraphStmt *it) {
	m_graph_stack.push_back(it);
}

void PSIVisitor::pop_graph() {
	if (m_graph_stack.size() > 0) {
		m_graph_stack.pop_back();
	}
}

IGraphStmt *PSIVisitor::graph_parent(IGraphStmt *it) {
	if (it) {
		fprintf(stdout, "it=%p\n", it);
		for (int32_t i=m_graph_stack.size()-1; i>=0; i--) {
			if (m_graph_stack.at(i) == it && i>0) {
				return m_graph_stack.at(i-1);
			}
		}
	} else {
		if (m_graph_stack.size() > 0) {
			return m_graph_stack.at(m_graph_stack.size()-1);
		}
	}
	return 0;
}

} /* namespace apps */
} /* namespace psi */
