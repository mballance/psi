/*
 * PSIProcessor.cpp
 *
 *  Created on: Jul 15, 2016
 *      Author: ballance
 */

#include "PSIVisitor.h"
#include "PSIUtil.h"
#include <stdio.h>

namespace psi {
namespace apps {

PSIVisitor::PSIVisitor() {
	// TODO Auto-generated constructor stub

}

PSIVisitor::~PSIVisitor() {
	// TODO Auto-generated destructor stub
}

void PSIVisitor::visit_model(IModel *model) {
	IPackage *pkg = model->getGlobalPackage();
	visit_package(pkg);

	std::vector<IBaseItem *>::const_iterator it=model->getItems().begin();

	for (; it!=model->getItems().end(); it++) {
		IBaseItem *i = *it;

		if (i->getType() == IBaseItem::TypePackage) {
			IPackage *pkg = static_cast<IPackage *>(i);
			visit_package(pkg);
		} else if (i->getType() == IBaseItem::TypeComponent) {
			visit_component(static_cast<IComponent *>(i));
		} else {
			// Really shouldn't be anything else in the global scope
		}
	}
}

void PSIVisitor::visit_package(IPackage *pkg) {
	std::vector<IBaseItem *>::const_iterator it=pkg->getItems().begin();

	for (; it!=pkg->getItems().end(); it++) {
		IBaseItem *i = *it;

		switch (i->getType()) {
			case IBaseItem::TypeAction:
				// TODO:
				break;

			case IBaseItem::TypeStruct:
				visit_struct(static_cast<IStruct *>(i));
				break;
		}
	}
}

void PSIVisitor::visit_action(IAction *a) {
	visit_body(a, a->getItems());

	if (a->getGraph()) {
		visit_graph(a->getGraph());
	}
}

void PSIVisitor::visit_bind(IBind *b) {

}

void PSIVisitor::visit_body(IBaseItem *p, const std::vector<IBaseItem *> &items) {
	std::vector<IBaseItem *>::const_iterator it = items.begin();

	for (; it!=items.end(); it++) {
		IBaseItem *i = *it;

		switch (i->getType()) {
		case IBaseItem::TypeBind:
			visit_bind(static_cast<IBind *>(i));
			break;
		case IBaseItem::TypeConstraint:
			visit_constraint(static_cast<IConstraintBlock *>(i));
			break;

		case IBaseItem::TypeField:
			visit_field(static_cast<IField *>(i));
			break;

		default:
			fprintf(stdout, "Error: Unknown body item %d\n", i->getType());
		}
	}
}

void PSIVisitor::visit_struct(IStruct *str) {
	visit_body(str, str->getItems());
}

void PSIVisitor::visit_component(IComponent *c) {

	visit_comp_pkg_body(c->getItems());

}

void PSIVisitor::visit_comp_pkg_body(const std::vector<IBaseItem *> &items) {
	std::vector<IBaseItem *>::const_iterator it=items.begin();

	for (; it!=items.end(); it++) {
		switch ((*it)->getType()) {
			case IBaseItem::TypeAction:
				visit_action(static_cast<IAction *>(*it));
				break;

			case IBaseItem::TypeStruct:
				visit_struct(static_cast<IStruct *>(*it));
				break;
		}
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

		visit_constraint_block(static_cast<IConstraintBlock *>(c));
	} break;

	case IConstraint::ConstraintType_Expr:
		visit_constraint_expr_stmt(static_cast<IConstraintExpr *>(c));
		break;

	case IConstraint::ConstraintType_If: {
		IConstraintIf *c_if = static_cast<IConstraintIf *>(c);

		visit_expr(c_if->getCond());

		visit_constraint_stmt(c_if->getTrue());

		if (c_if->getFalse()) {
			visit_constraint_stmt(c_if->getFalse());
		}
		} break;
	}
}

void PSIVisitor::visit_constraint_expr_stmt(IConstraintExpr *c) {
	visit_expr(c->getExpr());
}

void PSIVisitor::visit_constraint_block(IConstraintBlock *block) {
	std::vector<IConstraint *>::const_iterator it = block->getConstraints().begin();

	for (; it!=block->getConstraints().end(); it++) {
		IConstraint *c = *it;
		visit_constraint_stmt(c);
	}
}

void PSIVisitor::visit_expr(IExpr *e) {
	if (!e) {
		fprintf(stdout, "Error: null expression\n");
		return;
	}
	switch (e->getType()) {
		case IExpr::ExprType_BinOp: visit_binary_expr(static_cast<IBinaryExpr *>(e)); break;
		case IExpr::ExprType_FieldRef: visit_fieldref_expr(static_cast<IFieldRef *>(e)); break;
		case IExpr::ExprType_Literal: visit_literal_expr(static_cast<ILiteral *>(e)); break;
	}
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

	if (graph->getStmtType() == IGraphStmt::GraphStmt_Block) {
		IGraphBlockStmt *b = static_cast<IGraphBlockStmt *>(graph);
		for (std::vector<IGraphStmt *>::const_iterator it=b->getStmts().begin();
				it!=b->getStmts().end(); it++) {
			visit_graph_stmt(*it);
		}
	} else {
		visit_graph_stmt(graph);
	}
}

void PSIVisitor::visit_graph_stmt(IGraphStmt *stmt) {
	switch (stmt->getStmtType()) {
	case IGraphStmt::GraphStmt_Block: {
		visit_graph_block_stmt(static_cast<IGraphBlockStmt *>(stmt));
	} break;

	case IGraphStmt::GraphStmt_IfElse: {
		fprintf(stdout, "TODO: GraphStmt_IfElse\n");
	} break;

	case IGraphStmt::GraphStmt_Parallel: {
		visit_graph_block_stmt(static_cast<IGraphBlockStmt *>(stmt));
	} break;

	case IGraphStmt::GraphStmt_Schedule: {
		visit_graph_block_stmt(static_cast<IGraphBlockStmt *>(stmt));
	} break;

	case IGraphStmt::GraphStmt_Select: {
		visit_graph_block_stmt(static_cast<IGraphBlockStmt *>(stmt));
	} break;

	case IGraphStmt::GraphStmt_Repeat: {
		IGraphRepeatStmt *r = static_cast<IGraphRepeatStmt *>(stmt);

		// TODO: handle non-forever versions
		visit_graph_stmt(r->getBody());

	} break;

	case IGraphStmt::GraphStmt_Traverse: {
		IGraphTraverseStmt *t = static_cast<IGraphTraverseStmt *>(stmt);

		if (t->getWith()) {
			visit_constraint_stmt(t->getWith());
		}
	} break;

	default: fprintf(stdout, "TODO: handle graph stmt %d\n", stmt->getStmtType());

	}
}

void PSIVisitor::visit_graph_block_stmt(IGraphBlockStmt *block) {
	std::vector<IGraphStmt *>::const_iterator it;

	for (it=block->getStmts().begin(); it!=block->getStmts().end(); it++) {
		visit_graph_stmt(*it);
	}
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

} /* namespace apps */
} /* namespace psi */
