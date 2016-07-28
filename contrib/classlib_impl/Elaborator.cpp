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

#include "Elaborator.h"
#include "api/IComponent.h"
#include "api/IObjectContext.h"
#include "api/IInlineExec.h"
#include "BitTypeImp.h"
#include "ImportImp.h"
#include "IntTypeImp.h"
#include "BoolImp.h"
//#include "ChandleImp.h"
//#include "RepeatImp.h"
#include "ModelImp.h"
#include <stdio.h>
#include <stdarg.h>

#include "ExprCoreList.h"
#include "ExprImp.h"
#include "InlineExecClosure.h"

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

void Elaborator::elaborate(BaseItemImp *root, IModel *model) {
	vector<BaseItemImp *>::const_iterator it;

	m_model = model;

	// First, go through and declare global data types
	for (it=root->getChildren().begin(); it!=root->getChildren().end(); it++) {
		BaseItemImp *t = (*it);

		if (t->getObjectType() == BaseItemImp::TypeStruct) {
			IStruct *s = elaborate_struct(static_cast<StructImp *>(t));
			m_model->getGlobalPackage()->add(s);
		}
	}

	// Next, go through and declare global scopes
	for (it=root->getChildren().begin(); it!=root->getChildren().end(); it++) {
		BaseItemImp *t = (*it);

		if (t->getObjectType() == BaseItemImp::TypePackage) {
			elaborate_package(model, static_cast<PackageImp *>(t));
		} else if (t->getObjectType() == BaseItemImp::TypeComponent) {
			IComponent *c = elaborate_component(m_model, static_cast<ComponentImp *>(t));
			fprintf(stdout, "elaborate component: %s\n", c->getName().c_str());
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
		BaseItemImp *t = action->getChildren().at(i);
		bool filter = false;

		if (t->getObjectType() == BaseItemImp::TypeBind) {
			c = elaborate_bind(static_cast<BindImp *>(t));

			if (c) {
				a->add(c);
			} else {
				fprintf(stdout, "Error: failed to build bind item %s\n",
						BaseItemImp::toString(t->getObjectType()));
			}
		} if (t->getObjectType() == BaseItemImp::TypeGraph) {
			IGraphStmt *g = elaborate_graph(static_cast<GraphImp *>(t));
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

		if (t->getObjectType() == BaseItemImp::TypeAction) {
			IAction *a = elaborate_action(static_cast<ActionImp *>(t));
			comp->add(a);
		} else if (t->getObjectType() == BaseItemImp::TypeStruct) {
			IStruct *s = elaborate_struct(static_cast<StructImp *>(t));
			comp->add(s);
		} else if (t->getObjectType() == BaseItemImp::TypeField) {
			IField *f = elaborate_field_item(static_cast<FieldItemImp *>(t));
			comp->add(f);
		} else if (t->getObjectType() == BaseItemImp::TypeBind) {
			IBind *b = elaborate_bind(static_cast<BindImp *>(t));
			comp->add(b);
		} else {
			// TODO:
			fprintf(stdout, "Error: Unknown component body item %s\n",
					BaseItemImp::toString(t->getObjectType()));
		}
	}

	return comp;
}

IBind *Elaborator::elaborate_bind(BindImp *b) {
	IBind *ret = 0;
	std::vector<IBindPath *> targets;

	for (std::vector<BaseItemImp *>::const_iterator it=b->getChildren().begin();
			it!=b->getChildren().end(); it++) {
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
IConstraint *Elaborator::elaborate_constraint(ConstraintImp *c) {
	debug_low("--> elaborate_constraint %s",
			(c->getName() == "")?"UNNAMED":c->getName().c_str());
	IConstraintBlock *ret = m_model->mkConstraintBlock(c->getName());

	Expr &e = c->getStmt();

	if (e.imp().getOp() != ExprImp::List) {
		// Something is wrong here
		fprintf(stdout, "Internal Error: Expecting ExprList\n");
	}

	ExprCoreList *l = static_cast<ExprCoreList *>(e.imp().ptr());
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
		ret = elaborate_constraint_if(static_cast<ExprCoreIf *>(s));
	} else if (ExprImp::isBinOp(s->getOp())) {
		ret = m_model->mkConstraintExpr(elaborate_expr(s));
	} else if (s->getOp() == ExprImp::List) {
		IConstraintBlock *block = m_model->mkConstraintBlock("");


		ExprCoreList *l = static_cast<ExprCoreList *>(s);
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
				super_type = static_cast<IStruct *>(it_b);
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
//				static_cast<FieldItem *>(t)->isInternal()) {
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
			case BaseItemImp::TypeAction: c = elaborate_action(static_cast<ActionImp *>(t)); break;
			case BaseItemImp::TypeStruct: c = elaborate_struct(static_cast<StructImp *>(t)); break;
			case BaseItemImp::TypeExec:  c = elaborate_exec_item(static_cast<ExecImp *>(t)); break;
//			case BaseItemImp::TypeImport: c = elaborate_import(static_cast<Import *>(t)); break;
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

	if (t->getObjectType() == BaseItemImp::TypeConstraint) {
		ret = elaborate_constraint(static_cast<ConstraintImp *>(t));
	} else if (t->getObjectType() == BaseItemImp::TypeField) {
		ret = elaborate_field_item(static_cast<FieldItemImp *>(t));
	} else if (t->getObjectType() == BaseItemImp::TypeExec) {
		ret = elaborate_exec_item(static_cast<ExecImp *>(t));
	} else {

	}

	return ret;
}

IExec *Elaborator::elaborate_exec_item(ExecImp *e) {
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

	BaseItemImp *t = e->getParent();

	if (t->getObjectType() != BaseItemImp::TypeStruct &&
			t->getObjectType() != BaseItemImp::TypeAction) {
		error("Exec blocks can only be placed inside Action and Struct types. "
				"Invalid type: %s", BaseItemImp::toString(t->getObjectType()));
		return 0;
	}

	switch (e->getExecType()) {
	case ExecImp::Native: {

	} break;

	case ExecImp::Inline: {
		IInlineExec *inline_exec = 0;

		if (kind == IExec::PreSolve) {
			if (t->getObjectType() == BaseItemImp::TypeAction) {
				inline_exec = new InlineExecClosure<ActionImp>(
						static_cast<ActionImp *>(t),
						&ActionImp::inline_exec_pre,
						&ActionImp::pre_solve,
						&ActionImp::inline_exec_post);
			} else if (t->getObjectType() == BaseItemImp::TypeStruct) {
				inline_exec = new InlineExecClosure<StructImp>(
						static_cast<StructImp *>(t),
						&StructImp::inline_exec_pre,
						&StructImp::pre_solve,
						&StructImp::inline_exec_post);
			}
		} else if (kind == IExec::PostSolve) {
			if (t->getObjectType() == BaseItemImp::TypeAction) {
				inline_exec = new InlineExecClosure<ActionImp>(
						static_cast<ActionImp *>(t),
						&ActionImp::inline_exec_pre,
						&ActionImp::post_solve,
						&ActionImp::inline_exec_post);
			} else if (t->getObjectType() == BaseItemImp::TypeStruct) {
				inline_exec = new InlineExecClosure<StructImp>(
						static_cast<StructImp *>(t),
						&StructImp::inline_exec_pre,
						&StructImp::post_solve,
						&StructImp::inline_exec_post);
			}
		} else if (kind == IExec::Body) {
			if (t->getObjectType() == BaseItemImp::TypeAction) {
				inline_exec = new InlineExecClosure<ActionImp>(
						static_cast<ActionImp *>(t),
						&ActionImp::inline_exec_pre,
						&ActionImp::body,
						&ActionImp::inline_exec_post);
			} else if (t->getObjectType() == BaseItemImp::TypeStruct) {
				inline_exec = new InlineExecClosure<StructImp>(
						static_cast<StructImp *>(t),
						&StructImp::inline_exec_pre,
						&StructImp::body,
						&StructImp::inline_exec_post);
			}
		} else {
			error("unsupported inline exec block kind: %d", kind);
		}

		ret = m_model->mkInlineExec(kind, inline_exec);
	} break;

	case ExecImp::TargetTemplate: {
		fprintf(stdout, "Create TargetTemplate exec\n");
		ret = m_model->mkTargetTemplateExec(kind, e->getLanguage(), e->getTargetTemplate());
	} break;
	}

	return ret;
}

IField *Elaborator::elaborate_field_item(FieldItemImp *f) {
	IField *ret = 0;
	BaseItemImp *dt = f->getDataType();
	IField::FieldAttr attr = getAttr(f);
	IBaseItem *ft = 0;

	if (dt->getObjectType() == BaseItemImp::TypeBit) {
		// This is a bit-type field
		BitTypeImp *bt = static_cast<BitTypeImp *>(dt);
		ft = m_model->mkScalarType(
				IScalarType::ScalarType_Bit, bt->getMsb(), bt->getLsb());
	} else if (dt->getObjectType() == BaseItemImp::TypeInt) {
		// This is an int-type field
		IntTypeImp *it = static_cast<IntTypeImp *>(dt);
		ft = m_model->mkScalarType(
				IScalarType::ScalarType_Int, it->getMsb(), it->getLsb());
	} else if (dt->getObjectType() == BaseItemImp::TypeBool) {
		// Boolean field
		BoolImp *it = static_cast<BoolImp *>(dt);

		ft = m_model->mkScalarType(
				IScalarType::ScalarType_Bool, 0, 0);
	} else if (dt->getObjectType() == BaseItemImp::TypeChandle) {
		ft = m_model->mkScalarType(
				IScalarType::ScalarType_Chandle, 0, 0);
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
	}

	if (ft) {
		ret = m_model->mkField(f->getName(), ft, attr);
	}

	return ret;
}

IFieldRef *Elaborator::elaborate_field_ref(BaseItemImp *t) {
	std::vector<NamedBaseItemImp *>	types;
	std::vector<IField *> 			fields;

	debug_high("--> elaborate_field_ref: %p %d", t, (t)?t->getObjectType():0);

	while (t) {
		// Traverse up to the point where we find the
		// declaration scope that contains this expression
		if (t == m_class_expr_ctxt) {
			// TODO: might need to do something different for extended types?
			break;
		} else {
			NamedBaseItemImp *ni = toNamedItem(t);

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
			NamedBaseItemImp *t = types.at(i);
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
		NamedBaseItemImp *scope = toNamedItem(m_class_expr_ctxt);
		std::string name = (scope)?scope->getName():"UNKNOWN";
		error(std::string("Current context (") + name + ") is not a scope");
	}

	debug_high("<-- elaborate_field_ref");
	return m_model->mkFieldRef(fields);
}

IBindPath *Elaborator::elaborate_bind_path(BaseItemImp *t) {
	std::vector<NamedBaseItemImp *>	types;
	std::vector<IBaseItem *> 		path;

	debug_high("--> elaborate_field_ref: %p %d", t, (t)?t->getObjectType():0);

	while (t) {
		// Traverse up to the point where we find the
		// declaration scope that contains this expression
		if (t == m_class_expr_ctxt) {
			// TODO: might need to do something different for extended types?
			break;
		} else {
			NamedBaseItemImp *ni = toNamedItem(t);

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
			NamedBaseItemImp *t = types.at(i);
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
		NamedBaseItemImp *scope = toNamedItem(m_class_expr_ctxt);
		std::string name = (scope)?scope->getName():"UNKNOWN";
		error(std::string("Current context (") + name + ") is not a scope");
	}

	debug_high("<-- elaborate_field_ref");
	return m_model->mkBindPath(path);
}

IGraphStmt *Elaborator::elaborate_graph(GraphImp *g) {
	ExprList stmts = g->getSequence();
	ExprCoreList *stmts_c = static_cast<ExprCoreList *>(stmts.imp().ptr());
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
		ExprCoreList *stmt_l = static_cast<ExprCoreList *>(stmt);
		std::vector<ExprImp >::const_iterator it;
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

	case ExprImp::GraphRepeat: {
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
		fprintf(stdout, "Error: Unhandled graph stmt %d\n", stmt->getOp());
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
	case FieldItem::AttrInput: attr = IField::FieldAttr_Input; break;
	case FieldItem::AttrOutput: attr = IField::FieldAttr_Output; break;
	case FieldItem::AttrLock: attr = IField::FieldAttr_Lock; break;
	case FieldItem::AttrShare: attr = IField::FieldAttr_Share; break;
	case FieldItem::AttrRand: attr = IField::FieldAttr_Rand; break;
	case FieldItem::AttrPool: attr = IField::FieldAttr_Pool; break;
	}

	return attr;
}

BaseItemImp *Elaborator::find_cl_type_decl(const TypePathImp &path) {
	BaseItemImp *ret = 0;
	BaseItemImp *scope = ModelImp::global();

	for (std::vector<std::string>::const_iterator it=path.get().begin();
			it!=path.get().end(); it++) {
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

IBaseItem *Elaborator::find_type_decl(BaseItemImp *t) {
	IBaseItem *ret = 0;
	std::vector<NamedBaseItemImp *> type_p;

	NamedBaseItemImp *ti = toNamedItem(t);
	while (ti) {
		type_p.push_back(ti);
		ti = toNamedItem(ti->getParent());
	}

	IScopeItem *s = 0;
	for (int32_t i=type_p.size()-1; i>=0; i--) {
		ti = type_p.at(i);

		if (s) {
			ret = find_named_scope(s->getItems(), ti->getName());
		} else if (ti->getObjectType() != BaseItemImp::Model) { // Skip global-scope references
			// global search
			// First, do a global lookup for package and component items
			ret = find_named_scope(m_model->getItems(), ti->getName());

			if (!ret) {
				ret = find_named_scope(
						m_model->getGlobalPackage()->getItems(),
						ti->getName());
			}
		}

		if (!ret && ti->getObjectType() != BaseItemImp::Model) {
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
//			static_cast<FieldItem *>(item)->isInternal()) {
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
		// Now count how many instances are in this item. If there
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
		items.push_back(t);

		if (t->getObjectType() == BaseItemImp::TypeAction) {
			t = find_cl_type_decl(static_cast<ActionImp *>(t)->getSuperType());
		} else if (t->getObjectType() == BaseItemImp::TypeStruct) {
			t = find_cl_type_decl(static_cast<StructImp *>(t)->getSuperType());
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

NamedBaseItemImp *Elaborator::toNamedItem(BaseItemImp *it) {
	return NamedBaseItemImp::to(it);
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
