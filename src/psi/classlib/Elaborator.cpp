/*
 * PsiElaborator.cpp
 *
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
 *  Created on: May 2, 2016
 *      Author: ballance
 */

#include "classlib/Elaborator.h"
#include "api/IComponent.h"
#include "api/IObjectContext.h"
#include "api/IInlineExec.h"
#include "classlib/ExprCoreList.h"
#include "classlib/BitType.h"
#include "classlib/Import.h"
#include "classlib/IntType.h"
#include "classlib/Bool.h"
#include "classlib/Chandle.h"
#include "classlib/Repeat.h"
#include "classlib/Model.h"
#include "classlib/InlineExecClosure.h"

#include <stdio.h>
#include <stdarg.h>

namespace psi {

using namespace std;

Elaborator::Elaborator() : m_model(0),
		m_model_expr_ctxt(0), m_class_expr_ctxt(0),
		m_log_level(OFF) {
	// TODO Auto-generated constructor stub

}

Elaborator::~Elaborator() {
	// TODO Auto-generated destructor stub
}

void Elaborator::elaborate(BaseItem *root, IModel *model) {
	vector<BaseItem *>::const_iterator it;

	m_model = model;

	// First, go through and declare global data types
	for (it=root->getChildren().begin(); it!=root->getChildren().end(); it++) {
		BaseItem *t = (*it);

		if (t->getObjectType() == BaseItem::TypeStruct) {
			IStruct *s = elaborate_struct(static_cast<Struct *>(t));
			m_model->getGlobalPackage()->add(s);
		}
	}

	// Next, go through and declare global scopes
	for (it=root->getChildren().begin(); it!=root->getChildren().end(); it++) {
		BaseItem *t = (*it);

		if (t->getObjectType() == BaseItem::TypePackage) {
			elaborate_package(model, static_cast<Package *>(t));
		} else if (t->getObjectType() == BaseItem::TypeComponent) {
			IComponent *c = elaborate_component(m_model, static_cast<Component *>(t));
			fprintf(stdout, "elaborate component: %s\n", c->getName().c_str());
//			m_model->add(c);
		} else if (t->getObjectType() != BaseItem::TypeStruct) {
			// Error:
			error(std::string("Unsupported root element: ") +
					BaseItem::toString(t->getObjectType()));
		}
	}
}

IAction *Elaborator::elaborate_action(Action *action) {
	IAction 					*super_a = 0; // TODO:
	std::vector<BaseItem *>		type_h;

	if (!action->getSuperType().isNull()) {
		// Locate the type
		IBaseItem *it_b = find_type_decl(action->getSuperType());

		build_type_hierarchy(type_h, action);

		if (it_b->getType() == IBaseItem::TypeAction) {
			super_a = static_cast<IAction *>(it_b);
		}

		// TODO: error handling
	}
	IAction *a = m_model->mkAction(action->getName(), super_a);

	set_expr_ctxt(a, action);

	for (uint32_t i=0; i<action->getChildren().size(); i++) {
		IBaseItem *c = 0;
		BaseItem *t = action->getChildren().at(i);
		bool filter = false;

		if (t->getObjectType() == BaseItem::TypeBind) {
			c = elaborate_bind(static_cast<Bind *>(t));

			if (c) {
				a->add(c);
			} else {
				fprintf(stdout, "Error: failed to build bind item %s\n",
						BaseItem::toString(t->getObjectType()));
			}
		} if (t->getObjectType() == BaseItem::TypeGraph) {
			IGraphStmt *g = elaborate_graph(static_cast<Graph *>(t));
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
					fprintf(stdout, "Error: failed to build action child item %s\n",
							BaseItem::toString(t->getObjectType()));
				}
			}
		}
	}


	return a;
}

IComponent *Elaborator::elaborate_component(IScopeItem *scope, Component *c) {
	IComponent *comp = m_model->mkComponent(c->getName());
	if (scope) {
		scope->add(comp);
	}


	std::vector<BaseItem *>::const_iterator it = c->getChildren().begin();

	for (; it!=c->getChildren().end(); it++) {
		BaseItem *t = *it;

		set_expr_ctxt(comp, c);

		if (t->getObjectType() == BaseItem::TypeAction) {
			IAction *a = elaborate_action(static_cast<Action *>(t));
			comp->add(a);
		} else if (t->getObjectType() == BaseItem::TypeStruct) {
			IStruct *s = elaborate_struct(static_cast<Struct *>(t));
			comp->add(s);
		} else if (t->getObjectType() == BaseItem::TypeField) {
			IField *f = elaborate_field_item(static_cast<FieldItem *>(t));
			comp->add(f);
		} else if (t->getObjectType() == BaseItem::TypeBind) {
			IBind *b = elaborate_bind(static_cast<Bind *>(t));
			comp->add(b);
		} else {
			// TODO:
			fprintf(stdout, "Error: Unknown component body item %s\n",
					BaseItem::toString(t->getObjectType()));
		}
	}

	return comp;
}

IBind *Elaborator::elaborate_bind(Bind *b) {
	IBind *ret = 0;
	std::vector<IBindPath *> targets;

	for (std::vector<BaseItem *>::const_iterator it=b->getItems().begin();
			it!=b->getItems().end(); it++) {
		IBindPath *path = elaborate_bind_path(*it);

		if (path) {
			fprintf(stdout, "Found ref: %p\n", path);
			targets.push_back(path);
		} else {
			error("Failed to find bind reference");
		}
	}

	return m_model->mkBind(targets);
}

// TODO: should return
IConstraint *Elaborator::elaborate_constraint(Constraint *c) {
	debug_low("--> elaborate_constraint %s",
			(c->getName() == "")?"UNNAMED":c->getName().c_str());
	IConstraintBlock *ret = m_model->mkConstraintBlock(c->getName());

	Expr &e = c->getStmt();

	if (e.getOp() != Expr::List) {
		// Something is wrong here
		fprintf(stdout, "Internal Error: Expecting ExprList\n");
	}

	ExprCoreList *l = static_cast<ExprCoreList *>(e.getCore().ptr());
	std::vector<SharedPtr<ExprCore> >::const_iterator it = l->getExprList().begin();

	for (; it!=l->getExprList().end(); it++) {
		ExprCore *ec = it->ptr();

		IConstraint *c = elaborate_constraint_stmt(ec);
		ret->add(c);
	}

	debug_low("<-- elaborate_constraint %s",
			(c->getName() == "")?"UNNAMED":c->getName().c_str());

	return ret;
}

IConstraintIf *Elaborator::elaborate_constraint_if(ExprCoreIf *if_c) {
	IExpr *cond = elaborate_expr(if_c->getCond().getCorePtr());

	IConstraint *true_c = elaborate_constraint_stmt(
			if_c->getTrue().getCorePtr());

	IConstraint *false_c = 0;

	if (if_c->getFalse().getCorePtr()) {
		false_c = elaborate_constraint_stmt(
				if_c->getFalse().getCorePtr());
	}

	return m_model->mkConstraintIf(cond, true_c, false_c);
}

IConstraint *Elaborator::elaborate_constraint_stmt(ExprCore *s) {
	IConstraint *ret = 0;

	if (s->getOp() == Expr::Stmt_If || s->getOp() == Expr::Stmt_IfElse) {
		ret = elaborate_constraint_if(static_cast<ExprCoreIf *>(s));
	} else if (Expr::isBinOp(s->getOp())) {
		ret = m_model->mkConstraintExpr(elaborate_expr(s));
	} else if (s->getOp() == Expr::List) {
		IConstraintBlock *block = m_model->mkConstraintBlock("");


		ExprCoreList *l = static_cast<ExprCoreList *>(s);
		std::vector<SharedPtr<ExprCore> >::const_iterator it = l->getExprList().begin();
		for (; it!=l->getExprList().end(); it++) {
			block->add(elaborate_constraint_stmt(it->ptr()));
		}

		ret = block;
	} else {
		// Don't really know what's going on
		fprintf(stdout, "Error: unknown constraint statement %s\n",
				Expr::toString(s->getOp()));
	}

	return ret;
}

IExpr *Elaborator::elaborate_expr(ExprCore *e) {
	IExpr *ret = 0;

	switch (e->getOp()) {
	case Expr::LiteralUint:
	case Expr::LiteralBit:
		ret = m_model->mkBitLiteral(e->getValUI());
		break;
	case Expr::LiteralInt:
		ret = m_model->mkIntLiteral(e->getValI());
		break;
	case Expr::LiteralBool:
		ret = m_model->mkBoolLiteral(e->getValUI()?true:false);
		break;
	case Expr::LiteralString:
		fprintf(stdout, "Unsupported expression LiteralString\n");
		break;

	case Expr::BinOp_EqEq:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_EqEq,
				elaborate_expr(e->getRhsPtr()));
		break;
	case Expr::BinOp_NotEq:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_NotEq,
				elaborate_expr(e->getRhsPtr()));
		break;
	case Expr::BinOp_GE:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_GE,
				elaborate_expr(e->getRhsPtr()));
		break;
	case Expr::BinOp_GT:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_GT,
				elaborate_expr(e->getRhsPtr()));
		break;
	case Expr::BinOp_LE:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_LE,
				elaborate_expr(e->getRhsPtr()));
		break;
	case Expr::BinOp_LT:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_LT,
				elaborate_expr(e->getRhsPtr()));
		break;
	case Expr::BinOp_And:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_And,
				elaborate_expr(e->getRhsPtr()));
		break;
	case Expr::BinOp_AndAnd:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_AndAnd,
				elaborate_expr(e->getRhsPtr()));
		break;
	case Expr::BinOp_Or:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_Or,
				elaborate_expr(e->getRhsPtr()));
		break;
	case Expr::BinOp_OrOr:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_OrOr,
				elaborate_expr(e->getRhsPtr()));
		break;
	case Expr::BinOp_Minus:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_Minus,
				elaborate_expr(e->getRhsPtr()));
		break;
	case Expr::BinOp_Plus:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_Plus,
				elaborate_expr(e->getRhsPtr()));
		break;
	case Expr::BinOp_Multiply:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_Multiply,
				elaborate_expr(e->getRhsPtr()));
		break;
	case Expr::BinOp_Divide:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_Divide,
				elaborate_expr(e->getRhsPtr()));
		break;
	case Expr::BinOp_Mod:
		ret = m_model->mkBinExpr(
				elaborate_expr(e->getLhsPtr()),
				IBinaryExpr::BinOp_Mod,
				elaborate_expr(e->getRhsPtr()));
		break;
	case Expr::BinOp_ArrayRef:
		fprintf(stdout, "TODO: ArrayRef\n");
		break;

	case Expr::TypeRef: {
		ret = elaborate_field_ref(e->getTypePtr());
		} break;

	default:
		fprintf(stdout, "Error: unkown expression %s\n",
				Expr::toString(e->getOp()));
	}

	return ret;
}

IStruct *Elaborator::elaborate_struct(Struct *str) {
	IStruct::StructType t = IStruct::Base; // TODO:
	IStruct *super_type = 0;
	std::vector<BaseItem *>		type_h;

	if (!str->getSuperType().isNull()) {
		// Look for the actual type
		IBaseItem *it_b = find_type_decl(str->getSuperType());

		build_type_hierarchy(type_h, str);

		if (!it_b) {
			error(std::string("Failed to find struct type ") +
					str->getSuperType().toString());
		} else {
			if (it_b->getType() == IBaseItem::TypeStruct) {
				super_type = static_cast<IStruct *>(it_b);
			} else {
				error(std::string("Super type ") +
						str->getSuperType().toString());
			}
		}
	}

	switch (str->getStructType()) {
		case Struct::Memory: t = IStruct::Memory; break;
		case Struct::State: t = IStruct::State; break;
		case Struct::Stream: t = IStruct::Stream; break;
		case Struct::Resource: t = IStruct::Resource; break;
	}

	IStruct *s = m_model->mkStruct(str->getName(), t, super_type);

	set_expr_ctxt(s, str);

	for (uint32_t i=0; i<str->getChildren().size(); i++) {
		BaseItem *t = str->getChildren().at(i);
		bool filter = false;

		if (super_type) {
			filter = should_filter(str->getChildren(), i, type_h);
		} else if (t->getObjectType() == BaseItem::TypeField &&
				static_cast<FieldItem *>(t)->isInternal()) {
//			filter = true;
		}

		if (!filter) {
			IBaseItem *api_it = elaborate_struct_action_body_item(t);

			if (api_it) {
				s->add(api_it);
			} else {
				fprintf(stdout, "Error: failed to elaborate struct item: %s\n",
						BaseItem::toString(t->getObjectType()));
			}
		}
	}

	return s;
}

void Elaborator::elaborate_package(IModel *model, Package *pkg_cl) {
	IPackage *pkg = model->findPackage(pkg_cl->getName());

	if (pkg) {
		error("Multiple declaration of package " + pkg_cl->getName());
		return;
	}

	pkg = model->findPackage(pkg_cl->getName(), true);

	set_expr_ctxt(pkg, pkg_cl);

	for (std::vector<BaseItem *>::const_iterator it=pkg_cl->getChildren().begin();
			it!=pkg_cl->getChildren().end(); it++) {
		BaseItem *t = *it;
		IBaseItem *c = 0;

		switch (t->getObjectType()) {
			case BaseItem::TypeAction: c = elaborate_action(static_cast<Action *>(t)); break;
			case BaseItem::TypeStruct: c = elaborate_struct(static_cast<Struct *>(t)); break;
			case BaseItem::TypeExec:  c = elaborate_exec_item(static_cast<Exec *>(t)); break;
//			case BaseItem::TypeImport: c = elaborate_import(static_cast<Import *>(t)); break;
		}

		if (c) {
			pkg->add(c);
		} else {
			error("Unknown package body item %s",
					BaseItem::toString(t->getObjectType()));
		}
	}
}

IBaseItem *Elaborator::elaborate_struct_action_body_item(BaseItem *t) {
	IBaseItem *ret = 0;

	if (t->getObjectType() == BaseItem::TypeConstraint) {
		ret = elaborate_constraint(static_cast<Constraint *>(t));
	} else if (t->getObjectType() == BaseItem::TypeField) {
		ret = elaborate_field_item(static_cast<FieldItem *>(t));
	} else if (t->getObjectType() == BaseItem::TypeExec) {
		ret = elaborate_exec_item(static_cast<Exec *>(t));
	} else {

	}

	return ret;
}

IExec *Elaborator::elaborate_exec_item(Exec *e) {
	IExec *ret = 0;

	IExec::ExecKind kind = IExec::Body;
	switch (e->getExecKind()) {
	case Exec::Declaration: kind = IExec::Declaration; break;
	case Exec::Body: kind = IExec::Body; break;
	case Exec::PreSolve: kind = IExec::PreSolve; break;
	case Exec::PostSolve: kind = IExec::PostSolve; break;
	default:
		error("unhandled exec-block kind %d", e->getExecKind());
	}

	BaseItem *t = e->getParent();

	if (t->getObjectType() != BaseItem::TypeStruct &&
			t->getObjectType() != BaseItem::TypeAction) {
		error("Exec blocks can only be placed inside Action and Struct types. "
				"Invalid type: %s", BaseItem::toString(t->getObjectType()));
		return 0;
	}

	switch (e->getExecType()) {
	case Exec::Native: {

	} break;

	case Exec::Inline: {
		IInlineExec *inline_exec = 0;

		if (kind == IExec::PreSolve) {
			if (t->getObjectType() == BaseItem::TypeAction) {
				inline_exec = new InlineExecClosure<Action>(
						static_cast<Action *>(t),
						&Action::inline_exec_pre,
						&Action::pre_solve,
						&Action::inline_exec_post);
			} else if (t->getObjectType() == BaseItem::TypeStruct) {
				inline_exec = new InlineExecClosure<Struct>(
						static_cast<Struct *>(t),
						&Struct::inline_exec_pre,
						&Struct::pre_solve,
						&Struct::inline_exec_post);
			}
		} else if (kind == IExec::PostSolve) {
			if (t->getObjectType() == BaseItem::TypeAction) {
				inline_exec = new InlineExecClosure<Action>(
						static_cast<Action *>(t),
						&Action::inline_exec_pre,
						&Action::post_solve,
						&Action::inline_exec_post);
			} else if (t->getObjectType() == BaseItem::TypeStruct) {
				inline_exec = new InlineExecClosure<Struct>(
						static_cast<Struct *>(t),
						&Struct::inline_exec_pre,
						&Struct::post_solve,
						&Struct::inline_exec_post);
			}
		} else if (kind == IExec::Body) {
			if (t->getObjectType() == BaseItem::TypeAction) {
				inline_exec = new InlineExecClosure<Action>(
						static_cast<Action *>(t),
						&Action::inline_exec_pre,
						&Action::body,
						&Action::inline_exec_post);
			} else if (t->getObjectType() == BaseItem::TypeStruct) {
				inline_exec = new InlineExecClosure<Struct>(
						static_cast<Struct *>(t),
						&Struct::inline_exec_pre,
						&Struct::body,
						&Struct::inline_exec_post);
			}
		} else {
			error("unsupported inline exec block kind: %d", kind);
		}

		ret = m_model->mkInlineExec(kind, inline_exec);
	} break;

	case Exec::TargetTemplate: {
		fprintf(stdout, "Create TargetTemplate exec\n");
		ret = m_model->mkTargetTemplateExec(kind, e->getLanguage(), e->getTargetTemplate());
	} break;
	}

	return ret;
}

IField *Elaborator::elaborate_field_item(FieldItem *f) {
	IField *ret = 0;
	BaseItem *dt = f->getDataType();
	IField::FieldAttr attr = getAttr(f);
	IBaseItem *ft = 0;

	if (dt->getObjectType() == BaseItem::TypeBit) {
		// This is a bit-type field
		BitType *bt = static_cast<BitType *>(dt);
		ft = m_model->mkScalarType(
				IScalarType::ScalarType_Bit, bt->getMsb(), bt->getLsb());
	} else if (dt->getObjectType() == BaseItem::TypeInt) {
		// This is an int-type field
		IntType *it = static_cast<IntType *>(dt);
		ft = m_model->mkScalarType(
				IScalarType::ScalarType_Int, it->getMsb(), it->getLsb());
	} else if (dt->getObjectType() == BaseItem::TypeBool) {
		// Boolean field
		Bool *it = static_cast<Bool *>(dt);

		ft = m_model->mkScalarType(
				IScalarType::ScalarType_Bool, 0, 0);
	} else if (dt->getObjectType() == BaseItem::TypeChandle) {
		Chandle *it = static_cast<Chandle *>(dt);
		ft = m_model->mkScalarType(
				IScalarType::ScalarType_Chandle, 0, 0);
	} else if (dt->getObjectType() == BaseItem::TypeAction) {
		// This is an action-type field
		ft = find_type_decl(dt);
	} else if (dt->getObjectType() == BaseItem::TypeStruct) {
		// This is an struct-type field
		ft = find_type_decl(dt);
	} else if (dt->getObjectType() == BaseItem::TypeComponent) {
		// This is a component-type field
		ft = find_type_decl(dt);
	} else {
		// Error
	}

	if (ft) {
		ret = m_model->mkField(f->getName(), ft, attr);
	}

	return ret;
}

IFieldRef *Elaborator::elaborate_field_ref(BaseItem *t) {
	std::vector<NamedBaseItem *>	types;
	std::vector<IField *> 			fields;

	debug_high("--> elaborate_field_ref: %p %d", t, (t)?t->getObjectType():0);

	while (t) {
		// Traverse up to the point where we find the
		// declaration scope that contains this expression
		if (t == m_class_expr_ctxt) {
			// TODO: might need to do something different for extended types?
			break;
		} else {
			NamedBaseItem *ni = toNamedItem(t);

			if (ni) {
				debug_high("  Add type %s", ni->getName().c_str());
				types.push_back(ni);
			} else {
				debug_high("  Warn: element is not named");
			}
		}
		t = t->getParent();
	}

	// This is the active scope
	IScopeItem *scope = toScopeItem(m_model_expr_ctxt);
	if (scope) {
		// Traverse through the reference path built up above
		for (int32_t i=types.size()-1; i>=0; i--) {
			NamedBaseItem *t = types.at(i);
			IBaseItem *t_it = 0;

			IScopeItem *search_s = scope;
			while (search_s) {
				debug_high("Searching for %s in scope %s\n",
						t->getName().c_str(), getName(search_s));
				for (std::vector<IBaseItem *>::const_iterator s_it=search_s->getItems().begin();
						s_it!=search_s->getItems().end(); s_it++) {
					if ((*s_it)->getType() == IBaseItem::TypeField &&
							static_cast<IField *>(*s_it)->getName() == t->getName()) {
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
					IField *field = static_cast<IField *>(t_it);

					fields.push_back(field);

					if (i > 0) {
						if (field->getDataType()) {
							scope = toScopeItem(field->getDataType());

							if (!scope) {
								error(std::string("Field ") + t->getName() + " is not user-defined");
								break;
							}
						} else {
							error(std::string("Field ") + field->getName() + " doesn't have a type");
							break;
						}
					}
				}
			} else {
				INamedItem *named_it = toNamedItem(scope);
				error(std::string("Failed to find field ") + t->getName() +
						std::string(" in scope ") + ((named_it)?named_it->getName():"UNNAMED"));
				break;
			}
		}
	} else {
		NamedBaseItem *scope = toNamedItem(m_class_expr_ctxt);
		std::string name = (scope)?scope->getName():"UNKNOWN";
		error(std::string("Current context (") + name + ") is not a scope");
	}

	debug_high("<-- elaborate_field_ref");
	return m_model->mkFieldRef(fields);
}

IBindPath *Elaborator::elaborate_bind_path(BaseItem *t) {
	std::vector<NamedBaseItem *>	types;
	std::vector<IBaseItem *> 		path;

	debug_high("--> elaborate_field_ref: %p %d", t, (t)?t->getObjectType():0);

	while (t) {
		// Traverse up to the point where we find the
		// declaration scope that contains this expression
		if (t == m_class_expr_ctxt) {
			// TODO: might need to do something different for extended types?
			break;
		} else {
			NamedBaseItem *ni = toNamedItem(t);

			if (ni) {
				debug_high("  Add type %s", ni->getName().c_str());
				types.push_back(ni);
			} else {
				debug_high("  Warn: element is not named");
			}
		}
		t = t->getParent();
	}

	// This is the active scope
	IScopeItem *scope = toScopeItem(m_model_expr_ctxt);
	if (scope) {
		// Traverse through the reference path built up above
		for (int32_t i=types.size()-1; i>=0; i--) {
			NamedBaseItem *t = types.at(i);
			IBaseItem *t_it = 0;

			IScopeItem *search_s = scope;
			while (search_s) {
				debug_high("Searching for %s in scope %s\n",
						t->getName().c_str(), getName(search_s));
				for (std::vector<IBaseItem *>::const_iterator s_it=search_s->getItems().begin();
						s_it!=search_s->getItems().end(); s_it++) {
					if ((*s_it)->getType() == IBaseItem::TypeField &&
							static_cast<IField *>(*s_it)->getName() == t->getName()) {
						t_it = *s_it;
						break;
					} else if ((*s_it)->getType() == IBaseItem::TypeAction &&
							static_cast<IAction *>(*s_it)->getName() == t->getName()) {
						t_it = *s_it;
						break;
					} else if ((*s_it)->getType() == IBaseItem::TypeComponent &&
							static_cast<IComponent *>(*s_it)->getName() == t->getName()) {
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
					IField *field = static_cast<IField *>(t_it);

					if (i > 0) {
						if (field->getDataType()) {
							scope = toScopeItem(field->getDataType());

							if (!scope) {
								error(std::string("Field ") + t->getName() + " is not user-defined");
								break;
							}
						} else {
							error(std::string("Field ") + field->getName() + " doesn't have a type");
							break;
						}
					}
				} else if (t_it->getType() == IBaseItem::TypeAction) {
					scope = static_cast<IAction *>(t_it);
				} else if (t_it->getType() == IBaseItem::TypeComponent) {
					scope = static_cast<IComponent *>(t_it);
				}
			} else {
				INamedItem *named_it = toNamedItem(scope);
				error("Failed to find field %s in scope %s",
						t->getName().c_str(),
						toNamedItem(scope)?toNamedItem(scope)->getName().c_str():"UNNAMED");
				break;
			}
		}
	} else {
		NamedBaseItem *scope = toNamedItem(m_class_expr_ctxt);
		std::string name = (scope)?scope->getName():"UNKNOWN";
		error(std::string("Current context (") + name + ") is not a scope");
	}

	debug_high("<-- elaborate_field_ref");
	return m_model->mkBindPath(path);
}

IGraphStmt *Elaborator::elaborate_graph(Graph *g) {
	ExprList stmts = g->getSequence();
	if (stmts.getExprList().size() > 1) {
		std::vector<SharedPtr<ExprCore> >::const_iterator it;
		IGraphBlockStmt *block = m_model->mkGraphBlockStmt(IGraphStmt::GraphStmt_Block);

		for (it=stmts.getExprList().begin(); it!=stmts.getExprList().end(); it++) {
			IGraphStmt *stmt = elaborate_graph_stmt((*it).ptr());
			if (stmt) {
				block->add(stmt);
			} else {
				fprintf(stdout, "Error: failed to elaborate %d\n", (*it).ptr()->getOp());
			}
		}

		return block;
	} else {
		return elaborate_graph_stmt(stmts.getExprList().at(0).ptr());
	}
}

IGraphStmt *Elaborator::elaborate_graph_stmt(ExprCore *stmt) {
	IGraphStmt *ret = 0;

	switch (stmt->getOp()) {
	case Expr::GraphParallel:
	case Expr::GraphSelect:
	case Expr::GraphSchedule:
	case Expr::List: {
		// All are block statements
		IGraphBlockStmt *block = m_model->mkGraphBlockStmt(
				(stmt->getOp() == Expr::GraphParallel)?IGraphStmt::GraphStmt_Parallel:
						(stmt->getOp() == Expr::GraphSelect)?IGraphStmt::GraphStmt_Select:
						(stmt->getOp() == Expr::GraphSchedule)?IGraphStmt::GraphStmt_Schedule:
								IGraphStmt::GraphStmt_Block);
		ExprCoreList *stmt_l = static_cast<ExprCoreList *>(stmt);
		std::vector<SharedPtr<ExprCore> >::const_iterator it;
		for (it=stmt_l->getExprList().begin();
				it!=stmt_l->getExprList().end(); it++) {
			IGraphStmt *s = elaborate_graph_stmt((*it).ptr());
			if (s) {
				block->add(s);
			} else {
				fprintf(stdout, "Error: failed to elaborate %d\n",
						(*it).ptr()->getOp());
			}
		}
		ret = block;
	} break;

	case Expr::GraphRepeat: {
		// TODO: must handle other types
		IGraphRepeatStmt::RepeatType type = IGraphRepeatStmt::RepeatType_Count;

		IExpr *cond = 0;
		IGraphStmt *body;

		if (stmt->getLhsPtr()) {
			cond = elaborate_expr(stmt->getLhsPtr());
		}
		body = elaborate_graph_stmt(stmt->getRhsPtr());

		IGraphRepeatStmt *repeat_stmt = m_model->mkGraphRepeatStmt(
				type, cond, body);
		ret = repeat_stmt;
	} break;

	case Expr::TypeRef: {
		IFieldRef *ref = elaborate_field_ref(stmt->getTypePtr());

		if (ref) {
			ret = m_model->mkGraphTraverseStmt(ref, 0);
		} else {
			fprintf(stdout, "Error: failed to elaborate action ref\n");
		}
	} break;

	case Expr::GraphWith: {
		BaseItem *lhs = stmt->getLhsPtr()->getTypePtr();
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
		fprintf(stdout, "Error: Unhandled graph stmt %d\n", stmt->getOp());
	}

	return ret;
}

void Elaborator::set_expr_ctxt(IBaseItem *model_ctxt, BaseItem *class_ctxt) {
	m_model_expr_ctxt = model_ctxt;
	m_class_expr_ctxt = class_ctxt;
}

IField::FieldAttr Elaborator::getAttr(FieldItem *t) {
	IField::FieldAttr attr = IField::FieldAttr_None;

	switch (t->getAttr()) {
	case FieldItem::AttrInput: attr = IField::FieldAttr_Input; break;
	case FieldItem::AttrOutput: attr = IField::FieldAttr_Output; break;
	case FieldItem::AttrLock: attr = IField::FieldAttr_Lock; break;
	case FieldItem::AttrShare: attr = IField::FieldAttr_Share; break;
	case FieldItem::AttrRand: attr = IField::FieldAttr_Rand; break;
	case FieldItem::AttrPool: attr = IField::FieldAttr_Pool; break;
	}

	return attr;
}

BaseItem *Elaborator::find_cl_type_decl(const TypePath &path) {
	BaseItem *ret = 0;
	BaseItem *scope = Model::global();

	for (std::vector<std::string>::const_iterator it=path.get().begin();
			it!=path.get().end(); it++) {
		const std::string &it_s = (*it);
		const std::vector<BaseItem *> &item_v = scope->getChildren();
		fprintf(stdout, "  Path Elem: %s\n", (*it).c_str());

		BaseItem *o = 0;
		for (std::vector<BaseItem *>::const_iterator o_it=item_v.begin();
				o_it!=item_v.end(); o_it++) {
			NamedBaseItem *named_it = NamedBaseItem::to((*o_it));

			if (named_it && named_it->getName() == it_s) {
				o = *o_it;
				break;
			}
		}

		if (o) {
			ret = o;
			scope = o;
		} else {
			NamedBaseItem *scope_n = NamedBaseItem::to(scope);
			fprintf(stdout, "Error: Failed to find %s in scope %s\n",
					it_s.c_str(), (scope_n)?scope_n->getName().c_str():"UNNAMED");
			ret = 0;
			break;
		}

	}

	return ret;
}

IBaseItem *Elaborator::find_type_decl(const TypePath &path) {
	IScopeItem *s = 0;
	IBaseItem *ret;
	for (std::vector<std::string>::const_iterator it=path.get().begin();
			it!=path.get().end(); it++) {

		if (s) {
			ret = find_named_scope(s->getItems(), *it);
		} else {
			// global search
			// First, do a global lookup for package and component items
			ret = find_named_scope(m_model->getItems(), *it);

			if (!ret) {
				// Next, look for global data types
				ret = find_named_scope(
						m_model->getGlobalPackage()->getItems(), *it);
			}
		}

		if (!ret) {
			error(std::string("Failed to find type ") + *it);
			break;
		}

		s = toScopeItem(ret);

		if (!s) {
			break;
		}
	}

	return ret;
}

IBaseItem *Elaborator::find_type_decl(BaseItem *t) {
	IBaseItem *ret = 0;
	std::vector<NamedBaseItem *> type_p;

	NamedBaseItem *ti = toNamedItem(t);
	while (ti) {
		type_p.push_back(ti);
		ti = toNamedItem(ti->getParent());
	}

	IScopeItem *s = 0;
	for (int32_t i=type_p.size()-1; i>=0; i--) {
		ti = type_p.at(i);

		if (s) {
			ret = find_named_scope(s->getItems(), ti->getName());
		} else if (ti->getObjectType() != BaseItem::Model) { // Skip global-scope references
			// global search
			// First, do a global lookup for package and component items
			ret = find_named_scope(m_model->getItems(), ti->getName());

			if (!ret) {
				ret = find_named_scope(
						m_model->getGlobalPackage()->getItems(),
						ti->getName());
			}
		}

		if (!ret && ti->getObjectType() != BaseItem::Model) {
			error(std::string("Failed to find type ") + ti->getName());
			break;
		}

		s = toScopeItem(ret);

		if (!s) {
			break;
		}
	}

	return ret;
}

IBaseItem *Elaborator::find_named_scope(
		const std::vector<IBaseItem *>			&items,
		const std::string						&name) {
	IBaseItem *ret = 0;
	std::vector<IBaseItem *>::const_iterator it;

	for (it=items.begin(); it!=items.end(); it++) {
		INamedItem *named_it = toNamedItem(*it);

		if (named_it && named_it->getName() == name) {
			ret = *it;
			break;
		}
	}

	return ret;
}

bool Elaborator::should_filter(
		const std::vector<BaseItem *>	&items,
		uint32_t						i,
		const std::vector<BaseItem *>	&type_h) {
	// Base types are evaluated first
	// - Must preserve 'override' elements
	// - Must filter out re-declarations
	//
	// - Count of a given element in the parent type
	// - Count of a given element in this type
	// -> Preserve if parent count is 0
	// -> Preserve if
	bool ret = false;

	BaseItem *item = items.at(i);

//	if (item->getObjectType() == BaseItem::TypeField &&
//			static_cast<FieldItem *>(item)->isInternal()) {
//		// Always skip implementation fields
//		return true;
//	}
	NamedBaseItem *ni = toNamedItem(item);

	if (!ni || ni->getName() == "" || type_h.size() == 1) {
		debug_high("should_filter (false): name=\"%s\" type_h.size=%d\n",
				(ni)?ni->getName().c_str():"NULL",
				type_h.size());

		// Always preserve unnamed items
		return false;
	}

	// Count the occurrences of this item in the parent
	uint32_t parent_c = 0;

	BaseItem *p = type_h.at(1);
	for (std::vector<BaseItem *>::const_iterator it=p->getChildren().begin();
			it != p->getChildren().end(); it++) {
		BaseItem *t = *it;
		NamedBaseItem *ni_t = toNamedItem(t);

		if (t->getObjectType() == item->getObjectType() &&
				ni && ni_t && ni->getName() == ni_t->getName()) {
			parent_c++;
		}
	}

	if (parent_c > 0) {
		// Okay, the parent contains this item
		// Now count how many instances are in this item. If there
		// are more instances in this item AND we are pointing at the last,
		// then we can add. Otherwise, we filter
		uint32_t this_c = 0;
		uint32_t last_i = 0;

		for (uint32_t ii=0; ii<items.size(); ii++) {
			BaseItem *t = items.at(ii);
			NamedBaseItem *ni_t = toNamedItem(t);

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
		std::vector<BaseItem *>			&items,
		BaseItem						*t) {
	while (t) {
		items.push_back(t);

		if (t->getObjectType() == BaseItem::TypeAction) {
			t = find_cl_type_decl(static_cast<Action *>(t)->getSuperType());
		} else if (t->getObjectType() == BaseItem::TypeStruct) {
			t = find_cl_type_decl(static_cast<Struct *>(t)->getSuperType());
		} else {
			t = 0;
		}
	}
}

IScopeItem *Elaborator::toScopeItem(IBaseItem *it) {
	switch (it->getType()) {
	case IBaseItem::TypeAction: return static_cast<IAction *>(it);
	case IBaseItem::TypeStruct: return static_cast<IStruct *>(it);
	case IBaseItem::TypeComponent: return static_cast<IComponent *>(it);
	}
	return 0;
}

INamedItem *Elaborator::toNamedItem(IBaseItem *it) {
	switch (it->getType()) {
	case IBaseItem::TypeAction: return static_cast<IAction *>(it);
	case IBaseItem::TypeStruct: return static_cast<IStruct *>(it);
	case IBaseItem::TypeComponent: return static_cast<IComponent *>(it);
	case IBaseItem::TypeField: return static_cast<IField *>(it);
	case IBaseItem::TypePackage: return static_cast<IPackage *>(it);
	}
	return 0;
}

NamedBaseItem *Elaborator::toNamedItem(BaseItem *it) {
	return NamedBaseItem::to(it);
}

const char *Elaborator::getName(IBaseItem *it) {
	INamedItem *it_n = toNamedItem(it);

	if (it_n) {
		return it_n->getName().c_str();
	} else {
		return "UNNAMED";
	}
}

IScopeItem *Elaborator::getSuperType(IScopeItem *it) {
	switch (it->getType()) {
	case IBaseItem::TypeAction: return static_cast<IAction *>(it)->getSuperType();
	case IBaseItem::TypeStruct: return static_cast<IStruct *>(it)->getSuperType();
//	case IBaseItem::TypeComponent: return static_cast<IComponent *>(it)->getSuperType();
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

} /* namespace psi */
