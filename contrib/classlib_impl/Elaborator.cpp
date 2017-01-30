/*
 * PsiElaborator.cpp
 *
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
 *  Created on: May 2, 2016
 *      Author: ballance
 */

#include "Elaborator.h"
#include "api/IComponent.h"
#include "api/IExecCallback.h"
#include "BitTypeImp.h"
#include "ImportFuncImp.h"
#include "IntTypeImp.h"
#include "BoolImp.h"
#include "ModelImp.h"
#include "ExecStmtListImp.h"
#include "ExecStmtImp.h"
#include <stdio.h>
#include <stdarg.h>

#include "ExprCoreList.h"
#include "ExprImp.h"
#include "InlineExecClosure.h"
#include "ExecAssignCallStmtImp.h"
#include "ExecImportCallStmtImp.h"
#include "ExecAssignExprStmtImp.h"

namespace pss {

using namespace std;

Elaborator::Elaborator() : m_model(0),
		m_model_expr_ctxt(0), m_class_expr_ctxt(0),
		m_log_level(OFF) {
	// TODO Auto-generated constructor stub

}

Elaborator::~Elaborator() {
	// TODO Auto-generated destructor stub
}

void Elaborator::elaborate(BaseItemImp *root, IModel *model) {
	vector<BaseItemImp *>::const_iterator it;

	m_model = model;

	// First, go through and declare global data types
	for (it=root->getChildren().begin(); it!=root->getChildren().end(); it++) {
		BaseItemImp *t = (*it);

		if (t->getObjectType() == BaseItemImp::TypeStruct) {
			IStruct *s = elaborate_struct(dynamic_cast<StructImp *>(t));
			m_model->getGlobalPackage()->add(s);
		}
	}

	// Next, go through and declare global scopes
	debug_high("Root scope has %d items", root->getChildren().size());
	for (it=root->getChildren().begin(); it!=root->getChildren().end(); it++) {
		BaseItemImp *t = (*it);

		debug_high("  Root Item: %d", t->getObjectType());

		if (t->getObjectType() == BaseItemImp::TypePackage) {
			elaborate_package(model, dynamic_cast<PackageImp *>(t));
		} else if (t->getObjectType() == BaseItemImp::TypeComponent) {
			IComponent *c = elaborate_component(m_model, dynamic_cast<ComponentImp *>(t));
			debug_med("elaborate component: %s\n", c->getName().c_str());
//			m_model->add(c);
		} else if (t->getObjectType() != BaseItemImp::TypeStruct) {
			// Error:
			error(std::string("Unsupported root element: ") +
					BaseItemImp::toString(t->getObjectType()));
		}
	}
}

IAction *Elaborator::elaborate_action(ActionImp *action) {
	IAction 					*super_a = 0; // TODO:
	std::vector<BaseItemImp *>	type_h;

	if (!action->getSuperType().isNull()) {
		// Locate the type
		IBaseItem *it_b = find_type_decl(action->getSuperType());

		if (!it_b) {
			error("Failed to find super-type");
		}

		build_type_hierarchy(type_h, action);

		if (it_b->getType() == IBaseItem::TypeAction) {
			super_a = dynamic_cast<IAction *>(it_b);
		}

		// TODO: error handling
	}
	IAction *a = m_model->mkAction(action->getName(), super_a);

	set_expr_ctxt(a, action);

	for (uint32_t i=0; i<action->getChildren().size(); i++) {
		IBaseItem *c = 0;
		BaseItemImp *t = action->getChildren().at(i);
		bool filter = false;

		if (t->getObjectType() == BaseItemImp::TypeBind) {
			c = elaborate_bind(dynamic_cast<BindImp *>(t));

			if (c) {
				a->add(c);
			} else {
				error("Failed to build bind item %s\n",
						BaseItemImp::toString(t->getObjectType()));
			}
		} if (t->getObjectType() == BaseItemImp::TypeGraph) {
			IGraphStmt *g = elaborate_graph(dynamic_cast<ActivityImp *>(t));
			a->setGraph(g);
		} else {
			if (super_a) {
				filter = should_filter(action->getChildren(), i, type_h);
			}

			if (!filter) {
				c = elaborate_struct_action_body_item(t);

				if (c) {
					a->add(c);
				} else {
					error("failed to build action child item %s\n",
							BaseItemImp::toString(t->getObjectType()));
				}
			}
		}
	}


	return a;
}

IComponent *Elaborator::elaborate_component(IScopeItem *scope, ComponentImp *c) {
	IComponent *comp = m_model->mkComponent(c->getName());
	if (scope) {
		scope->add(comp);
	}


	std::vector<BaseItemImp *>::const_iterator it = c->getChildren().begin();

	for (; it!=c->getChildren().end(); it++) {
		BaseItemImp *t = *it;

		set_expr_ctxt(comp, c);

		IBaseItem *item = elaborate_component_body_item(t);

		if (item) {
			comp->add(item);
		}
	}

	return comp;
}

IBaseItem *Elaborator::elaborate_component_body_item(BaseItemImp *t) {
	IBaseItem *ret = 0;

	if (t->getObjectType() == BaseItemImp::TypeAction) {
		ret = elaborate_action(dynamic_cast<ActionImp *>(t));
	} else if (t->getObjectType() == BaseItemImp::TypeStruct) {
		ret = elaborate_struct(dynamic_cast<StructImp *>(t));
	} else if (t->getObjectType() == BaseItemImp::TypeField) {
		ret = elaborate_field_item(dynamic_cast<FieldItemImp *>(t));
	} else if (t->getObjectType() == BaseItemImp::TypeBind) {
		ret = elaborate_bind(dynamic_cast<BindImp *>(t));
	} else {
		// TODO:
		error("Unknown component body item %s\n",
				BaseItemImp::toString(t->getObjectType()));
	}

	return ret;
}

IBind *Elaborator::elaborate_bind(BindImp *b) {
	IBind *ret = 0;
	std::vector<IBindPath *> targets;

	for (std::vector<BaseItemImp *>::const_iterator it=b->getChildren().begin();
			it!=b->getChildren().end(); it++) {
		IBindPath *path = elaborate_bind_path(*it);

		if (path) {
			targets.push_back(path);
		} else {
			error("Failed to find bind reference");
		}
	}

	return m_model->mkBind(targets);
}

// TODO: should return
IConstraint *Elaborator::elaborate_constraint(ConstraintImp *c) {
	debug_low("--> elaborate_constraint %s",
			(c->getName() == "")?"UNNAMED":c->getName().c_str());
	IConstraintBlock *ret = m_model->mkConstraintBlock(c->getName());

	expr &e = c->getStmt();

	if (e.imp().getOp() != ExprImp::List) {
		// Something is wrong here
		error("Internal Error: Expecting expr_list\n");
	}

	ExprCoreList *l = dynamic_cast<ExprCoreList *>(e.imp().ptr());
	std::vector<ExprImp >::const_iterator it = l->getExprList().begin();

	for (; it!=l->getExprList().end(); it++) {
		ExprCore *ec = (*it).ptr();

		IConstraint *c = elaborate_constraint_stmt(ec);
		ret->add(c);
	}

	debug_low("<-- elaborate_constraint %s",
			(c->getName() == "")?"UNNAMED":c->getName().c_str());

	return ret;
}

IConstraintIf *Elaborator::elaborate_constraint_if(ExprCoreIf *if_c) {
	IExpr *cond = elaborate_expr(if_c->getCond().ptr());

	IConstraint *true_c = elaborate_constraint_stmt(
			if_c->getTrue().ptr());

	IConstraint *false_c = 0;

	if (if_c->getFalse().ptr()) {
		false_c = elaborate_constraint_stmt(
				if_c->getFalse().ptr());
	}

	return m_model->mkConstraintIf(cond, true_c, false_c);
}

IConstraint *Elaborator::elaborate_constraint_stmt(ExprCore *s) {
	IConstraint *ret = 0;

	if (s->getOp() == ExprImp::Stmt_If || s->getOp() == ExprImp::Stmt_IfElse) {
		ret = elaborate_constraint_if(dynamic_cast<ExprCoreIf *>(s));
	} else if (s->getOp() == ExprImp::Stmt_Implies) {
		ret = m_model->mkConstraintImplies(
				elaborate_expr(s->getLhsPtr()),
				elaborate_constraint_stmt(s->getRhsPtr()));
	} else if (ExprImp::isBinOp(s->getOp())) {
		ret = m_model->mkConstraintExpr(elaborate_expr(s));
	} else if (s->getOp() == ExprImp::List) {
		IConstraintBlock *block = m_model->mkConstraintBlock("");


		ExprCoreList *l = dynamic_cast<ExprCoreList *>(s);
		std::vector<ExprImp >::const_iterator it = l->getExprList().begin();
		for (; it!=l->getExprList().end(); it++) {
			block->add(elaborate_constraint_stmt((*it).ptr()));
		}

		ret = block;
	} else {
		// Don't really know what's going on
		fprintf(stdout, "Error: unknown constraint statement %s\n",
				ExprImp::toString(s->getOp()));
	}

	return ret;
}

IExpr *Elaborator::elaborate_expr(ExprCore *e) {
	IExpr *ret = 0;

	switch (e->getOp()) {
	case ExprImp::LiteralUint:
	case ExprImp::LiteralBit:
		ret = m_model->mkBitLiteral(e->getValUI());
		break;
	case ExprImp::LiteralInt:
		ret = m_model->mkIntLiteral(e->getValI());
		break;
	case ExprImp::LiteralBool:
		ret = m_model->mkBoolLiteral(e->getValUI()?true:false);
		break;
	case ExprImp::LiteralString:
		fprintf(stdout, "Unsupported expression LiteralString\n");
		break;

	case ExprImp::BinOp_EqEq:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_EqEq,
				elaborate_expr(e->getRhsPtr()));
		break;
	case ExprImp::BinOp_NotEq:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_NotEq,
				elaborate_expr(e->getRhsPtr()));
		break;
	case ExprImp::BinOp_GE:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_GE,
				elaborate_expr(e->getRhsPtr()));
		break;
	case ExprImp::BinOp_GT:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_GT,
				elaborate_expr(e->getRhsPtr()));
		break;
	case ExprImp::BinOp_LE:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_LE,
				elaborate_expr(e->getRhsPtr()));
		break;
	case ExprImp::BinOp_LT:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_LT,
				elaborate_expr(e->getRhsPtr()));
		break;
	case ExprImp::BinOp_And:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_And,
				elaborate_expr(e->getRhsPtr()));
		break;
	case ExprImp::BinOp_AndAnd:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_AndAnd,
				elaborate_expr(e->getRhsPtr()));
		break;
	case ExprImp::BinOp_Or:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_Or,
				elaborate_expr(e->getRhsPtr()));
		break;
	case ExprImp::BinOp_OrOr:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_OrOr,
				elaborate_expr(e->getRhsPtr()));
		break;
	case ExprImp::BinOp_Minus:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_Minus,
				elaborate_expr(e->getRhsPtr()));
		break;
	case ExprImp::BinOp_Plus:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_Plus,
				elaborate_expr(e->getRhsPtr()));
		break;
	case ExprImp::BinOp_Multiply:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_Multiply,
				elaborate_expr(e->getRhsPtr()));
		break;
	case ExprImp::BinOp_Divide:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_Divide,
				elaborate_expr(e->getRhsPtr()));
		break;
	case ExprImp::BinOp_Mod:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_Mod,
				elaborate_expr(e->getRhsPtr()));
		break;
	case ExprImp::BinOp_ArrayRef:
		fprintf(stdout, "TODO: ArrayRef\n");
		break;

	case ExprImp::TypeRef: {
		ret = elaborate_field_ref(e->getTypePtr());
		} break;

	default:
		fprintf(stdout, "Error: unkown expression %s\n",
				ExprImp::toString(e->getOp()));
	}

	return ret;
}

IStruct *Elaborator::elaborate_struct(StructImp *str) {
	IStruct::StructType t = IStruct::Base; // TODO:
	IStruct *super_type = 0;
	std::vector<BaseItemImp *>		type_h;

	if (!str->getSuperType().isNull()) {
		// Look for the actual type
		IBaseItem *it_b = find_type_decl(str->getSuperType());

		build_type_hierarchy(type_h, str);

		if (!it_b) {
			error(std::string("Failed to find struct type ") +
					str->getSuperType().toString());
		} else {
			if (it_b->getType() == IBaseItem::TypeStruct) {
				super_type = dynamic_cast<IStruct *>(it_b);
			} else {
				error(std::string("Super type ") +
						str->getSuperType().toString());
			}
		}
	}

	switch (str->getStructType()) {
		case StructImp::Memory: t = IStruct::Memory; break;
		case StructImp::State: t = IStruct::State; break;
		case StructImp::Stream: t = IStruct::Stream; break;
		case StructImp::Resource: t = IStruct::Resource; break;
	}

	IStruct *s = m_model->mkStruct(str->getName(), t, super_type);

	set_expr_ctxt(s, str);

	for (uint32_t i=0; i<str->getChildren().size(); i++) {
		BaseItemImp *t = str->getChildren().at(i);
		bool filter = false;

		if (super_type) {
			filter = should_filter(str->getChildren(), i, type_h);
		}
//		else if (t->getObjectType() == BaseItemImp::TypeField &&
//				dynamic_cast<attr_item *>(t)->isInternal()) {
//			filter = true;
//		}

		if (!filter) {
			IBaseItem *api_it = elaborate_struct_action_body_item(t);

			if (api_it) {
				s->add(api_it);
			} else {
				fprintf(stdout, "Error: failed to elaborate struct item: %s\n",
						BaseItemImp::toString(t->getObjectType()));
			}
		}
	}

	return s;
}

void Elaborator::elaborate_package(IModel *model, PackageImp *pkg_cl) {
	IPackage *pkg = model->findPackage(pkg_cl->getName());

	if (pkg) {
		error("Multiple declaration of package " + pkg_cl->getName());
		return;
	}

	pkg = model->findPackage(pkg_cl->getName(), true);

	set_expr_ctxt(pkg, pkg_cl);

	for (std::vector<BaseItemImp *>::const_iterator it=pkg_cl->getChildren().begin();
			it!=pkg_cl->getChildren().end(); it++) {
		BaseItemImp *t = *it;
		IBaseItem *c = 0;

		switch (t->getObjectType()) {
			case BaseItemImp::TypeAction: c = elaborate_action(dynamic_cast<ActionImp *>(t)); break;
			case BaseItemImp::TypeStruct: c = elaborate_struct(dynamic_cast<StructImp *>(t)); break;
//			case BaseItemImp::TypeExec:  c = elaborate_exec_item(dynamic_cast<ExecImp *>(t)); break;
			case BaseItemImp::TypeImport: c = elaborate_import_func(dynamic_cast<ImportFuncImp *>(t)); break;
			case BaseItemImp::TypeExtendAction:
			case BaseItemImp::TypeExtendComponent:
			case BaseItemImp::TypeExtendStruct:
				c = elaborate_extend(dynamic_cast<ExtendItemImp *>(t));
				break;
		}

		if (c) {
			pkg->add(c);
		} else {
			error("Unknown package body item %s",
					BaseItemImp::toString(t->getObjectType()));
		}
	}
}

IBaseItem *Elaborator::elaborate_struct_action_body_item(BaseItemImp *t) {
	IBaseItem *ret = 0;

	switch (t->getObjectType()) {
	case BaseItemImp::TypeConstraint:
		ret = elaborate_constraint(dynamic_cast<ConstraintImp *>(t));
		break;

	case BaseItemImp::TypeField:
		ret = elaborate_field_item(dynamic_cast<FieldItemImp *>(t));
		break;

	case BaseItemImp::TypeExec:
		ret = elaborate_exec_item(dynamic_cast<ExecImp *>(t));
		break;

	default:
		fprintf(stdout, "Error: unhandled struct/action-body item %d\n",
				t->getObjectType());
	}

	return ret;
}

IExec *Elaborator::elaborate_exec_item(ExecImp *e) {
	IExec *ret = 0;

	IExec::ExecKind kind = IExec::Body;
	switch (e->getExecKind()) {
	case exec::Declaration: kind = IExec::Declaration; break;
	case exec::Body: kind = IExec::Body; break;
	case exec::PreSolve: kind = IExec::PreSolve; break;
	case exec::PostSolve: kind = IExec::PostSolve; break;
	default:
		error("unhandled exec-block kind %d", e->getExecKind());
	}

	BaseItemImp *t = e->getParent();

	if (t->getObjectType() != BaseItemImp::TypeStruct &&
			t->getObjectType() != BaseItemImp::TypeAction) {
		error("exec blocks can only be placed inside action and pss_struct types. "
				"Invalid type: %s", BaseItemImp::toString(t->getObjectType()));
		return 0;
	}

	switch (e->getExecType()) {
	case ExecImp::Native: {
		const std::vector<exec_stmt> &stmts = static_cast<ExecImp *>(e)->getStmtList().imp()->stmts();
		std::vector<IExecStmt *> stmts_e;

		for (std::vector<exec_stmt>::const_iterator it=stmts.begin();
				it!=stmts.end(); it++) {
			stmts_e.push_back(elaborate_exec_stmt((*it).imp()));
		}
		ret = m_model->mkNativeExec(kind, stmts_e);
	} break;

	case ExecImp::Inline: {
		IExecCallback *inline_exec = 0;

		if (kind == IExec::PreSolve) {
			if (t->getObjectType() == BaseItemImp::TypeAction) {
				inline_exec = new InlineExecClosure<ActionImp>(
						dynamic_cast<ActionImp *>(t),
						&ActionImp::inline_exec_pre,
						&ActionImp::pre_solve,
						&ActionImp::inline_exec_post);
			} else if (t->getObjectType() == BaseItemImp::TypeStruct) {
				inline_exec = new InlineExecClosure<StructImp>(
						dynamic_cast<StructImp *>(t),
						&StructImp::inline_exec_pre,
						&StructImp::pre_solve,
						&StructImp::inline_exec_post);
			}
		} else if (kind == IExec::PostSolve) {
			if (t->getObjectType() == BaseItemImp::TypeAction) {
				inline_exec = new InlineExecClosure<ActionImp>(
						dynamic_cast<ActionImp *>(t),
						&ActionImp::inline_exec_pre,
						&ActionImp::post_solve,
						&ActionImp::inline_exec_post);
			} else if (t->getObjectType() == BaseItemImp::TypeStruct) {
				inline_exec = new InlineExecClosure<StructImp>(
						dynamic_cast<StructImp *>(t),
						&StructImp::inline_exec_pre,
						&StructImp::post_solve,
						&StructImp::inline_exec_post);
			}
		} else if (kind == IExec::Body) {
			if (t->getObjectType() == BaseItemImp::TypeAction) {
				inline_exec = new InlineExecClosure<ActionImp>(
						dynamic_cast<ActionImp *>(t),
						&ActionImp::inline_exec_pre,
						&ActionImp::body,
						&ActionImp::inline_exec_post);
			} else if (t->getObjectType() == BaseItemImp::TypeStruct) {
				error("struct types do not support body() exec blocks");
			}
		} else {
			error("unsupported inline exec block kind: %d", kind);
		}

		ret = m_model->mkInlineExec(kind, inline_exec);
	} break;

	case ExecImp::TargetTemplate: {
		ret = m_model->mkTargetTemplateExec(kind, e->getLanguage(), e->getTargetTemplate());
	} break;
	}

	return ret;
}

IExecStmt *Elaborator::elaborate_exec_stmt(ExecStmtImp *e) {
	IExecStmt *ret = 0;

	IExecStmt::AssignOp op = IExecStmt::AssignOp_None;

	ExecAssignStmtImp *assign = dynamic_cast<ExecAssignStmtImp *>(e);

	if (assign) {
		switch (assign->getOp()) {
		case ExecAssignStmtImp::AssignOp_Eq: op = IExecStmt::AssignOp_Eq; break;
		case ExecAssignStmtImp::AssignOp_PlusEq: op = IExecStmt::AssignOp_PlusEq; break;
		case ExecAssignStmtImp::AssignOp_MinusEq: op = IExecStmt::AssignOp_MinusEq; break;
		case ExecAssignStmtImp::AssignOp_LShiftEq: op = IExecStmt::AssignOp_LShiftEq; break;
		case ExecAssignStmtImp::AssignOp_RShiftEq: op = IExecStmt::AssignOp_RShiftEq; break;
		case ExecAssignStmtImp::AssignOp_AndEq: op = IExecStmt::AssignOp_AndEq; break;
		case ExecAssignStmtImp::AssignOp_OrEq: op = IExecStmt::AssignOp_OrEq; break;
		}
	}

	switch (e->getStmtType()) {
	case ExecStmtImp::StmtType_Call: {
		// Call to import function with no assignment
		ExecImportCallStmtImp *c = dynamic_cast<ExecImportCallStmtImp *>(e);
		IImportFunc *f = find_import_func(c->getFunc());
		std::vector<IExpr *> parameters;

		ExprCoreList *p_l;
		p_l = static_cast<ExprCoreList *>(c->getParameterList().imp().ptr());

		for (std::vector<ExprImp>::const_iterator it=p_l->getExprList().begin();
				it!=p_l->getExprList().end(); it++) {
			parameters.push_back(elaborate_expr((*it).ptr()));
		}

		ret = m_model->mkExecCallStmt(0, op, f, parameters);
	} break;

	case ExecStmtImp::StmtType_AssignCall: {
		// Call to import function with assignment
		ExecAssignCallStmtImp *c = dynamic_cast<ExecAssignCallStmtImp *>(e);
		ExecImportCallStmtImp *call = dynamic_cast<ExecImportCallStmtImp *>(c->rhs().imp());
		IImportFunc *f = find_import_func(call->getFunc());
		std::vector<IExpr *> parameters;

		IFieldRef *target = elaborate_field_ref(c->lhs().impl());

		ExprCoreList *p_l;
		p_l = static_cast<ExprCoreList *>(call->getParameterList().imp().ptr());

		for (std::vector<ExprImp>::const_iterator it=p_l->getExprList().begin();
				it!=p_l->getExprList().end(); it++) {
			parameters.push_back(elaborate_expr((*it).ptr()));
		}

		ret = m_model->mkExecCallStmt(target, op, f, parameters);
	} break;

	case ExecStmtImp::StmtType_AssignExpr: {
		// Expression assigned to field
		ExecAssignExprStmtImp *a = dynamic_cast<ExecAssignExprStmtImp *>(e);
		IFieldRef *target = elaborate_field_ref(a->lhs().impl());

		IExpr *rhs = elaborate_expr(a->rhs().imp().ptr());

		ret = m_model->mkExecExprStmt(target, op, rhs);
	} break;

	}

	return ret;
}

IExtend *Elaborator::elaborate_extend(ExtendItemImp *e) {
	BaseItemImp *t = e->getDataType();
	IBaseItem *target = find_type_decl(t); // Target type

	BaseItemImp *ext_h = e->getExtHndl();

	if (!target) {
		error("Failed to find target of extension: %s\n",
				dynamic_cast<NamedBaseItemImp *>(t)->getName().c_str());
	}

	IExtend *ret = m_model->mkExtend(target);

	for (uint32_t i=t->getChildren().size(); i<ext_h->getChildren().size(); i++) {
		BaseItemImp *item_c = ext_h->getChildren().at(i);
		IBaseItem *item = 0;
		set_expr_ctxt(target, t);

		if (t->getObjectType() == BaseItemImp::TypeComponent) {
			item = elaborate_component_body_item(item_c);
		} else {
			item = elaborate_struct_action_body_item(item_c);
		}

		if (item) {
			ret->add(item);
		} else {
			error("Failed to elaborate extension child %d", item_c->getObjectType());
		}
	}

	return ret;
}

IField *Elaborator::elaborate_field_item(FieldItemImp *f) {
	IField *ret = 0;
	BaseItemImp *dt = f->getDataType();
	IField::FieldAttr attr = getAttr(f);
	IBaseItem *ft = 0;
	IExpr *array_dim = 0;

	if (f->hasArrayDim()) {
		array_dim = elaborate_expr(f->arrayDim().ptr());
	}

	ft = elaborate_datatype(dt);

	if (ft) {
		ret = m_model->mkField(f->getName(), ft, attr, array_dim);
	}

	return ret;
}

IBaseItem *Elaborator::elaborate_datatype(BaseItemImp *dt) {
	IBaseItem *ft = 0;

	if (dt->getObjectType() == BaseItemImp::TypeBit) {
		// This is a bit-type field
		BitTypeImp *bt = dynamic_cast<BitTypeImp *>(dt);
		ft = m_model->mkScalarType(IScalarType::ScalarType_Bit,
				m_model->mkBitLiteral(bt->getMsb()),
				m_model->mkBitLiteral(bt->getLsb()));
	} else if (dt->getObjectType() == BaseItemImp::TypeInt) {
		// This is an int-type field
		IntTypeImp *it = dynamic_cast<IntTypeImp *>(dt);
		ft = m_model->mkScalarType(IScalarType::ScalarType_Int,
				m_model->mkBitLiteral(it->getMsb()),
				m_model->mkBitLiteral(it->getLsb()));
	} else if (dt->getObjectType() == BaseItemImp::TypeBool) {
		// Boolean field
		BoolImp *it = dynamic_cast<BoolImp *>(dt);

		ft = m_model->mkScalarType(
				IScalarType::ScalarType_Bool, 0, 0);
	} else if (dt->getObjectType() == BaseItemImp::TypeChandle) {
		ft = m_model->mkScalarType(
				IScalarType::ScalarType_Chandle, 0, 0);
	} else if (dt->getObjectType() == BaseItemImp::TypeString) {
		ft = m_model->mkScalarType(
				IScalarType::ScalarType_String, 0, 0);
	} else if (dt->getObjectType() == BaseItemImp::TypeAction) {
		// This is an action-type field
		ft = find_type_decl(dt);
	} else if (dt->getObjectType() == BaseItemImp::TypeStruct) {
		// This is an struct-type field
		ft = find_type_decl(dt);
	} else if (dt->getObjectType() == BaseItemImp::TypeComponent) {
		// This is a component-type field
		ft = find_type_decl(dt);
	} else {
		// Error
		fprintf(stdout, "Error: unsupported datatype %d\n", dt->getObjectType());
	}

	return ft;
}

IFieldRef *Elaborator::elaborate_field_ref(BaseItemImp *t) {
	std::vector<NamedBaseItemImp *>	types;
	std::vector<IField *> 			fields;
	NamedBaseItemImp *ni;
	NamedBaseItemImp *ni_i = dynamic_cast<NamedBaseItemImp *>(m_class_expr_ctxt);

	debug_high("--> elaborate_field_ref: %p %d", t, (t)?t->getObjectType():0);

	while (t) {
		// Traverse up to the point where we find the
		// declaration scope that contains this expression
		//
		// In most cases, can count on object identity. In the case
		// of type extension, we also check the object-type code
		// and the object names
		if (t == m_class_expr_ctxt ||
				(t->getObjectType() == m_class_expr_ctxt->getObjectType() &&
						ni_i && (ni = dynamic_cast<NamedBaseItemImp *>(t)) &&
						ni_i->getName() == ni->getName())) {
			// TODO: might need to do something different for extended types?
			debug_high("Reached t==m_class_expr_ctxt");
			break;
		} else {
			NamedBaseItemImp  *ni = dynamic_cast<NamedBaseItemImp *>(t);

			if (ni) {
				debug_high("  Add type %s (%p)", ni->getName().c_str(), t);
				types.push_back(ni);
			} else {
				debug_high("  Warn: element is not named (%d)", t->getObjectType());
			}
		}
		t = t->getParent();
		if (!t) {
			debug_high("  parent==null");
		}
	}

	// This is the active scope
	IScopeItem *scope = toScopeItem(m_model_expr_ctxt);
	if (scope) {
		// Traverse through the reference path built up above
		for (int32_t i=types.size()-1; i>=0; i--) {
			NamedBaseItemImp *t = types.at(i);
			IBaseItem *t_it = 0;

			IScopeItem *search_s = scope;
			while (search_s) {
				debug_high("Searching for %s in scope %s\n",
						t->getName().c_str(), getName(search_s));
				for (std::vector<IBaseItem *>::const_iterator s_it=search_s->getItems().begin();
						s_it!=search_s->getItems().end(); s_it++) {
					if ((*s_it)->getType() == IBaseItem::TypeField &&
							dynamic_cast<IField *>(*s_it)->getName() == t->getName()) {
						t_it = *s_it;
						break;
					}
				}
				if (t_it) {
					break;
				}

				// Traverse the inheritance hierarchy
				search_s = getSuperType(search_s);
			}

			if (t_it) {
				if (t_it->getType() == IBaseItem::TypeField) {
					IField *field = dynamic_cast<IField *>(t_it);

					fields.push_back(field);

					if (i > 0) {
						if (field->getDataType()) {
							scope = toScopeItem(field->getDataType());

							if (!scope) {
								error(std::string("attr ") + t->getName() + " is not user-defined");
								break;
							}
						} else {
							error(std::string("attr ") + field->getName() + " doesn't have a type");
							break;
						}
					}
				}
			} else {
				error("Failed to find field %p name=%s in scope %p %s",
						t, t->getName().c_str(), scope, getName(scope));
				break;
			}
		}
	} else {
		NamedBaseItemImp *scope = toNamedItem(m_class_expr_ctxt);
		std::string name = (scope)?scope->getName():"UNKNOWN";
		error(std::string("Current context (") + name + ") is not a scope");
	}

	debug_high("<-- elaborate_field_ref");
	return m_model->mkFieldRef(fields);
}

IImportFunc *Elaborator::elaborate_import_func(ImportFuncImp *imp) {
	std::vector<IField *> parameters;
	IBaseItem *ret = 0;

	if (imp->getReturnType()) {
		ret = elaborate_datatype(imp->getReturnType());
	}

	const std::vector<attr_item> &param_spec =
			imp->getParameters().imp()->parameters();

	for (std::vector<attr_item>::const_iterator it=param_spec.begin();
			it!=param_spec.end(); it++) {
		FieldItemImp *p = dynamic_cast<FieldItemImp *>((*it).impl());
		IBaseItem *pt = elaborate_datatype(p->getDataType());

		IField::FieldAttr attr;
		switch (p->getAttr()) {
		case attr_item::AttrInput: attr = IField::FieldAttr_Input; break;
		case attr_item::AttrOutput: attr = IField::FieldAttr_Output; break;
		case attr_item::AttrInout: attr = IField::FieldAttr_Inout; break;
		}

		fprintf(stdout, "parameter: %s\n", p->getName().c_str());
		IField *p_h = m_model->mkField(p->getName(), pt, attr, 0);
		parameters.push_back(p_h);
	}

	return m_model->mkImportFunc(
			imp->getName(),
			ret,
			parameters);
}

IBindPath *Elaborator::elaborate_bind_path(BaseItemImp *t) {
	std::vector<NamedBaseItemImp *>	types;
	std::vector<IBaseItem *> 		path;

	debug_high("--> elaborate_bind_path: %p %d", t, (t)?t->getObjectType():0);

	while (t) {
		// Traverse up to the point where we find the
		// declaration scope that contains this expression
		if (t == m_class_expr_ctxt) {
			// TODO: might need to do something different for extended types?
			debug_high("  Reached context scope");
			break;
		} else {
			NamedBaseItemImp *ni = toNamedItem(t);

			if (ni) {
				debug_high("  Add path elem %s", ni->getName().c_str());
				types.push_back(ni);
			} else {
				debug_high("  Warn: element is not named (%d)", t->getObjectType());
			}
		}
		t = t->getParent();
		debug_high("  parent=%p", t);
	}

	// This is the active scope
	IScopeItem *scope = toScopeItem(m_model_expr_ctxt);
	if (scope) {
		// Traverse through the reference path built up above
		for (int32_t i=types.size()-1; i>=0; i--) {
			NamedBaseItemImp *t = types.at(i);
			IBaseItem *t_it = 0;

			IScopeItem *search_s = scope;
			while (search_s) {
				debug_high("Searching for %s in scope %s\n",
						t->getName().c_str(), getName(search_s));
				for (std::vector<IBaseItem *>::const_iterator s_it=search_s->getItems().begin();
						s_it!=search_s->getItems().end(); s_it++) {
					if ((*s_it)->getType() == IBaseItem::TypeField &&
							dynamic_cast<IField *>(*s_it)->getName() == t->getName()) {
						t_it = *s_it;
						break;
					} else if ((*s_it)->getType() == IBaseItem::TypeAction &&
							dynamic_cast<IAction *>(*s_it)->getName() == t->getName()) {
						t_it = *s_it;
						break;
					} else if ((*s_it)->getType() == IBaseItem::TypeComponent &&
							dynamic_cast<IComponent *>(*s_it)->getName() == t->getName()) {
						t_it = *s_it;
						break;
					}
				}

				if (t_it) {
					break;
				}

				// Traverse the inheritance hierarchy
				search_s = getSuperType(search_s);
			}

			if (t_it) {
				path.push_back(t_it);
				if (t_it->getType() == IBaseItem::TypeField) {
					IField *field = dynamic_cast<IField *>(t_it);

					if (i > 0) {
						if (field->getDataType()) {
							scope = toScopeItem(field->getDataType());

							if (!scope) {
								error(std::string("attr ") + t->getName() + " is not user-defined");
								break;
							}
						} else {
							error(std::string("attr ") + field->getName() + " doesn't have a type");
							break;
						}
					}
				} else if (t_it->getType() == IBaseItem::TypeAction) {
					scope = dynamic_cast<IAction *>(t_it);
				} else if (t_it->getType() == IBaseItem::TypeComponent) {
					scope = dynamic_cast<IComponent *>(t_it);
				}
			} else {
				error("Failed to find field %s in scope %s",
						t->getName().c_str(), getName(scope));
				break;
			}
		}
	} else {
		NamedBaseItemImp *scope = toNamedItem(m_class_expr_ctxt);
		std::string name = (scope)?scope->getName():"UNKNOWN";
		error(std::string("Current context (") + name + ") is not a scope");
	}

	debug_high("<-- elaborate_bind_path");
	return m_model->mkBindPath(path);
}

IGraphStmt *Elaborator::elaborate_graph(ActivityImp *g) {
	expr_list stmts = g->getSequence();
	ExprCoreList *stmts_c = dynamic_cast<ExprCoreList *>(stmts.imp().ptr());
	if (stmts_c->getExprList().size() > 1) {
		std::vector<ExprImp >::const_iterator it;
		IGraphBlockStmt *block = m_model->mkGraphBlockStmt(IGraphStmt::GraphStmt_Block);

		for (it=stmts_c->getExprList().begin();
				it!=stmts_c->getExprList().end(); it++) {
			IGraphStmt *stmt = elaborate_graph_stmt((*it).ptr());
			if (stmt) {
				block->add(stmt);
			} else {
				fprintf(stdout, "Error: failed to elaborate %d\n", (*it).ptr()->getOp());
			}
		}

		return block;
	} else {
		return elaborate_graph_stmt(stmts_c->getExprList().at(0).ptr());
	}
}

IGraphStmt *Elaborator::elaborate_graph_stmt(ExprCore *stmt) {
	IGraphStmt *ret = 0;

	switch (stmt->getOp()) {
	case ExprImp::GraphParallel:
	case ExprImp::GraphSelect:
	case ExprImp::GraphSchedule:
	case ExprImp::List: {
		// All are block statements
		IGraphBlockStmt *block = m_model->mkGraphBlockStmt(
				(stmt->getOp() == ExprImp::GraphParallel)?IGraphStmt::GraphStmt_Parallel:
						(stmt->getOp() == ExprImp::GraphSelect)?IGraphStmt::GraphStmt_Select:
						(stmt->getOp() == ExprImp::GraphSchedule)?IGraphStmt::GraphStmt_Schedule:
								IGraphStmt::GraphStmt_Block);
		ExprCoreList *stmt_l = dynamic_cast<ExprCoreList *>(stmt);
		std::vector<ExprImp >::const_iterator it;
		for (it=stmt_l->getExprList().begin();
				it!=stmt_l->getExprList().end(); it++) {
			IGraphStmt *s = elaborate_graph_stmt((*it).ptr());
			if (s) {
				if (s->getStmtType() != IGraphStmt::GraphStmt_Block) {
					IGraphBlockStmt *block = m_model->mkGraphBlockStmt(IGraphStmt::GraphStmt_Block);
					block->add(s);
					s = block;
				}
				block->add(s);
			} else {
				fprintf(stdout, "Error: failed to elaborate %d\n",
						(*it).ptr()->getOp());
			}
		}
		ret = block;
	} break;

	case ExprImp::GraphRepeat: {
		// TODO: must handle other types
		IGraphRepeatStmt::RepeatType type = IGraphRepeatStmt::RepeatType_Count;

		IExpr *cond = 0;
		IGraphStmt *body;

		if (stmt->getLhsPtr()) {
			cond = elaborate_expr(stmt->getLhsPtr());
		}
		body = elaborate_graph_stmt(stmt->getRhsPtr());

		if (body->getStmtType() != IGraphStmt::GraphStmt_Block) {
			IGraphBlockStmt *block = m_model->mkGraphBlockStmt(
					IGraphStmt::GraphStmt_Block);
			block->add(body);
			body = block;
		}

		IGraphRepeatStmt *repeat_stmt = m_model->mkGraphRepeatStmt(
				type, cond, body);
		ret = repeat_stmt;
	} break;

	case ExprImp::TypeRef: {
		IFieldRef *ref = elaborate_field_ref(stmt->getTypePtr());

		if (ref) {
			ret = m_model->mkGraphTraverseStmt(ref, 0);
		} else {
			fprintf(stdout, "Error: failed to elaborate action ref\n");
		}
	} break;

	case ExprImp::GraphWith: {
		BaseItemImp *lhs = stmt->getLhsPtr()->getTypePtr();
		IFieldRef *ref = elaborate_field_ref(lhs); // stmt->getTypePtr());
		IConstraint *c = elaborate_constraint_stmt(stmt->getRhsPtr());

		if (ref) {
			ret = m_model->mkGraphTraverseStmt(ref, c);
		} else {
			fprintf(stdout, "Error: failed to elaborate action ref\n");
		}
	} break;

	}

	if (!ret) {
		fprintf(stdout, "Error: Unhandled activity stmt %d\n", stmt->getOp());
	}

	return ret;
}

void Elaborator::set_expr_ctxt(IBaseItem *model_ctxt, BaseItemImp *class_ctxt) {
	m_model_expr_ctxt = model_ctxt;
	m_class_expr_ctxt = class_ctxt;
}

IField::FieldAttr Elaborator::getAttr(FieldItemImp *t) {
	IField::FieldAttr attr = IField::FieldAttr_None;

	switch (t->getAttr()) {
	case attr_item::AttrInput: attr = IField::FieldAttr_Input; break;
	case attr_item::AttrOutput: attr = IField::FieldAttr_Output; break;
	case attr_item::AttrLock: attr = IField::FieldAttr_Lock; break;
	case attr_item::AttrShare: attr = IField::FieldAttr_Share; break;
	case attr_item::AttrRand: attr = IField::FieldAttr_Rand; break;
	case attr_item::AttrPool: attr = IField::FieldAttr_Pool; break;
	}

	return attr;
}

BaseItemImp *Elaborator::find_cl_type_decl(const TypePathImp &path) {
	BaseItemImp *ret = 0;
	BaseItemImp *scope = ModelImp::global();

	const std::vector<std::string> &pl = path.get();
	for (std::vector<std::string>::const_iterator it=pl.begin();
			it!=pl.end(); it++) {
		const std::string &it_s = (*it);
		const std::vector<BaseItemImp *> &item_v = scope->getChildren();
		fprintf(stdout, "  Path Elem: %s\n", (*it).c_str());

		BaseItemImp *o = 0;
		for (std::vector<BaseItemImp *>::const_iterator o_it=item_v.begin();
				o_it!=item_v.end(); o_it++) {
			NamedBaseItemImp *named_it = NamedBaseItemImp::to((*o_it));

			if (named_it && named_it->getName() == it_s) {
				o = *o_it;
				break;
			}
		}

		if (o) {
			ret = o;
			scope = o;
		} else {
			NamedBaseItemImp *scope_n = NamedBaseItemImp::to(scope);
			fprintf(stdout, "Error: Failed to find %s in scope %s\n",
					it_s.c_str(), (scope_n)?scope_n->getName().c_str():"UNNAMED");
			ret = 0;
			break;
		}

	}

	return ret;
}

IBaseItem *Elaborator::find_type_decl(const TypePathImp &path) {
	IScopeItem *s = 0;
	IBaseItem *ret;
	debug_high("--> find_type_decl: %s", path.toString().c_str());
	for (std::vector<std::string>::const_iterator it=path.get().begin();
			it!=path.get().end(); it++) {

		if (s) {
			ret = find_named_scope(s->getItems(), *it);
		} else {
			// global search
			// First, do a global lookup for package and component items
			debug_high("  Global search for %s", (*it).c_str());
			ret = find_named_scope(m_model->getItems(), *it);

			if (!ret) {
				debug_high("    => Failed - looking in global package");
				// Next, look for global data types
				ret = find_named_scope(
						m_model->getGlobalPackage()->getItems(), *it);
			} else {
				debug_high("    => Success");
			}
		}

		if (!ret) {
			error(std::string("Failed to find type ") + *it);
			break;
		}

		s = dynamic_cast<IScopeItem *>(ret);

		if (!s) {
			debug_high("  Item %d (%s) is not a scope",
					(ret)?ret->getType():-1, getName(ret));
			break;
		}
	}

	debug_high("<-- find_type_decl: %s (%s)", path.toString().c_str(), getName(ret));
	return ret;
}

IBaseItem *Elaborator::find_type_decl(BaseItemImp *t) {
	IBaseItem *ret = 0;
	std::vector<NamedBaseItemImp *> type_p;

	debug_high("--> find_type_decl %p (%s)", t, getName(t));

	NamedBaseItemImp *ti = toNamedItem(t);
	while (ti) {
		debug_high("  -- path: %s", ti->getName().c_str());
		type_p.push_back(ti);
		ti = dynamic_cast<NamedBaseItemImp *>(ti->getParent());
	}


	IScopeItem *s = 0;
	for (int32_t i=type_p.size()-1; i>=0; i--) {
		ti = type_p.at(i);

		if (s) {
			ret = find_named_scope(s->getItems(), ti->getName());
			if (!ret) {
				error("Failed to find type %s in scope %s",
						ti->getName().c_str(), getName(s));
			}
		} else if (ti->getObjectType() != BaseItemImp::Model) { // Skip global-scope references
			// global search
			// First, do a global lookup for package and component items
			ret = find_named_scope(m_model->getItems(), ti->getName());

			if (!ret) {
				debug_high("  -- Failed to find scope %s in global scope",
						ti->getName().c_str());
				ret = find_named_scope(
						m_model->getGlobalPackage()->getItems(),
						ti->getName());
			}

			if (!ret) {
				error(" -- Failed to find scope %s in global or global package scope",
						ti->getName().c_str());
			}
		}

		if (!ret && ti->getObjectType() != BaseItemImp::Model) {
			error(std::string("Failed to find type ") + ti->getName());
			break;
		}

		s = dynamic_cast<IScopeItem *>(ret);

		if (ret && !s) {
			debug_high(" -- found non-scope item %d\n", ret->getType());
		}

		if (!s) {
			break;
		}
	}

	debug_high("<-- find_type_decl %p (%s) => %p (%s)", t, getName(t), ret, getName(ret));
	return ret;
}

IImportFunc *Elaborator::find_import_func(ImportFuncImp *imp) {
	debug_high("--> find_import_func %p (%s)", imp, imp->getName().c_str());
	IBaseItem *it = find_type_decl(imp);

	IImportFunc *ret = dynamic_cast<IImportFunc *>(it);
	if (!ret && it) {
		error("Returned item is not an import function");
	}

	debug_high("<-- find_import_func %p (%s) %p", imp, imp->getName().c_str(), ret);
	return ret;
}

IBaseItem *Elaborator::find_named_scope(
		const std::vector<IBaseItem *>			&items,
		const std::string						&name) {
	IBaseItem *ret = 0;
	std::vector<IBaseItem *>::const_iterator it;

	for (it=items.begin(); it!=items.end(); it++) {
		INamedItem *named_it = dynamic_cast<INamedItem *>(*it);

		if (named_it && named_it->getName() == name) {
			ret = *it;
			break;
		}
	}

	return ret;
}

bool Elaborator::should_filter(
		const std::vector<BaseItemImp *>	&items,
		uint32_t						i,
		const std::vector<BaseItemImp *>	&type_h) {
	// Base types are evaluated first
	// - Must preserve 'override' elements
	// - Must filter out re-declarations
	//
	// - Count of a given element in the parent type
	// - Count of a given element in this type
	// -> Preserve if parent count is 0
	// -> Preserve if
	bool ret = false;

	BaseItemImp *item = items.at(i);

//	if (item->getObjectType() == BaseItemImp::TypeField &&
//			dynamic_cast<attr_item *>(item)->isInternal()) {
//		// Always skip implementation fields
//		return true;
//	}
	NamedBaseItemImp *ni = toNamedItem(item);

	if (!ni || ni->getName() == "" || type_h.size() == 1) {
		debug_high("should_filter (false): name=\"%s\" type_h.size=%d\n",
				(ni)?ni->getName().c_str():"NULL",
				type_h.size());

		// Always preserve unnamed items
		return false;
	}

	// Count the occurrences of this item in the parent
	uint32_t parent_c = 0;

	BaseItemImp *p = type_h.at(1);
	for (std::vector<BaseItemImp *>::const_iterator it=p->getChildren().begin();
			it != p->getChildren().end(); it++) {
		BaseItemImp *t = *it;
		NamedBaseItemImp *ni_t = toNamedItem(t);

		if (t->getObjectType() == item->getObjectType() &&
				ni && ni_t && ni->getName() == ni_t->getName()) {
			parent_c++;
		}
	}

	if (parent_c > 0) {
		// Okay, the parent contains this item
		// Now count how many instances are in this item. pss_if there
		// are more instances in this item AND we are pointing at the last,
		// then we can add. Otherwise, we filter
		uint32_t this_c = 0;
		uint32_t last_i = 0;

		for (uint32_t ii=0; ii<items.size(); ii++) {
			BaseItemImp *t = items.at(ii);
			NamedBaseItemImp *ni_t = toNamedItem(t);

			if (t->getObjectType() == item->getObjectType() &&
					ni && ni_t && ni->getName() == ni_t->getName()) {
				this_c++;
				last_i = ii;
			}
		}

		if (this_c <= parent_c || i < last_i) {
			ret = true;
		}
	}
	debug_high("should_filter (%s): name=\"%s\" type_h.size=%d\n",
			(ret)?"true":"false",
			(ni)?ni->getName().c_str():"NULL",
			type_h.size());

	return ret;
}

void Elaborator::build_type_hierarchy(
		std::vector<BaseItemImp *>			&items,
		BaseItemImp						*t) {
	while (t) {
		BaseItemImp *new_t = 0;
		items.push_back(t);

		if (t->getObjectType() == BaseItemImp::TypeAction) {
			new_t = find_cl_type_decl(dynamic_cast<ActionImp *>(t)->getSuperType());
		} else if (t->getObjectType() == BaseItemImp::TypeStruct) {
			new_t = find_cl_type_decl(dynamic_cast<StructImp *>(t)->getSuperType());
		}

		if (t == new_t) {
			error("Super-type cannot be self");
			t = 0;
		} else {
			t = new_t;
		}
	}
}

IScopeItem *Elaborator::toScopeItem(IBaseItem *it) {
	switch (it->getType()) {
	case IBaseItem::TypeAction: return dynamic_cast<IAction *>(it);
	case IBaseItem::TypeStruct: return dynamic_cast<IStruct *>(it);
	case IBaseItem::TypeComponent: return dynamic_cast<IComponent *>(it);
	}
	return 0;
}

INamedItem *Elaborator::toNamedItem(IBaseItem *it) {
	switch (it->getType()) {
	case IBaseItem::TypeAction: return dynamic_cast<IAction *>(it);
	case IBaseItem::TypeStruct: return dynamic_cast<IStruct *>(it);
	case IBaseItem::TypeComponent: return dynamic_cast<IComponent *>(it);
	case IBaseItem::TypeField: return dynamic_cast<IField *>(it);
	case IBaseItem::TypePackage: return dynamic_cast<IPackage *>(it);
	}
	return 0;
}

NamedBaseItemImp *Elaborator::toNamedItem(BaseItemImp *it) {
	return NamedBaseItemImp::to(it);
}

const char *Elaborator::getName(IBaseItem *it) {
	INamedItem *it_n = dynamic_cast<INamedItem *>(it);

	if (it_n) {
		return it_n->getName().c_str();
	} else {
		return "UNNAMED";
	}
}

const char *Elaborator::getName(IScopeItem *it) {
	INamedItem *it_n = dynamic_cast<INamedItem *>(it);

	if (it_n) {
		return it_n->getName().c_str();
	} else {
		return "UNNAMED";
	}
}

const char *Elaborator::getName(BaseItemImp *it) {

	if (it) {
	NamedBaseItemImp *it_n = dynamic_cast<NamedBaseItemImp *>(it);

	if (it_n) {
		return it_n->getName().c_str();
	} else {
		return "UNNAMED";
	}
	} else {
		return "NULL";
	}
}

IScopeItem *Elaborator::getSuperType(IScopeItem *it) {
	if (dynamic_cast<IAction *>(it)) {
		return dynamic_cast<IAction *>(it)->getSuperType();
	} else if (dynamic_cast<IStruct *>(it)) {
		return dynamic_cast<IStruct *>(it)->getSuperType();
	}

	return 0;
}

void Elaborator::error(const char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);

	fputs("Error: ", stdout);
	vfprintf(stdout, fmt, ap);
	fputs("\n", stdout);

	va_end(ap);
}

void Elaborator::error(const std::string &msg) {
	fprintf(stdout, "Error: %s\n", msg.c_str());
}

void Elaborator::debug(LogLevel l, const char *fmt, va_list ap) {

	if (m_log_level >= l) {
		fputs("DEBUG: ", stdout);
		vfprintf(stdout, fmt, ap);
		fputs("\n", stdout);
	}

}

void Elaborator::debug(LogLevel l, const char *fmt, ...) {
	va_list ap;

	if (m_log_level >= l) {
		va_start(ap, fmt);
		debug(l, fmt, ap);
		va_end(ap);
	}
}

void Elaborator::debug_low(const char *fmt, ...) {
	va_list ap;

	if (m_log_level >= LOW) {
		va_start(ap, fmt);
		debug(LOW, fmt, ap);
		va_end(ap);
	}
}

void Elaborator::debug_med(const char *fmt, ...) {
	va_list ap;

	if (m_log_level >= MED) {
		va_start(ap, fmt);
		debug(MED, fmt, ap);
		va_end(ap);
	}
}

void Elaborator::debug_high(const char *fmt, ...) {
	va_list ap;

	if (m_log_level >= HIGH) {
		va_start(ap, fmt);
		debug(HIGH, fmt, ap);
		va_end(ap);
	}
}

} /* namespace pss */
