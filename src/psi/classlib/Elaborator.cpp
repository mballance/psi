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
#include "classlib/ExprCoreList.h"
#include "classlib/BitType.h"
#include "classlib/Import.h"
#include "classlib/IntType.h"
#include "classlib/Bool.h"
#include "classlib/Chandle.h"
#include "classlib/Repeat.h"
#include "classlib/Model.h"

#include <stdio.h>

namespace psi {

using namespace std;

Elaborator::Elaborator() : m_model(0),
		m_model_expr_ctxt(0), m_class_expr_ctxt(0) {
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

IAction *Elaborator::elaborate_action(Action *c) {
	IAction *super_a = 0; // TODO:

	if (!c->getSuperType().isNull()) {
		// Locate the type
		IBaseItem *t = find_type_decl(c->getSuperType());

		if (t->getType() == IBaseItem::TypeAction) {
			super_a = static_cast<IAction *>(t);
		}

		// TODO: error handling
	}
	IAction *a = m_model->mkAction(c->getName(), super_a);

	set_expr_ctxt(a, c);

	std::vector<BaseItem *>::const_iterator it=c->getChildren().begin();

	for (; it!=c->getChildren().end(); it++) {
		IBaseItem *c = 0;
		if ((*it)->getObjectType() == BaseItem::TypeBind) {
			c = elaborate_bind(static_cast<Bind *>(*it));

			if (c) {
				a->add(c);
			} else {
				fprintf(stdout, "Error: failed to build action child item %s\n",
						BaseItem::toString((*it)->getObjectType()));
			}
		} if ((*it)->getObjectType() == BaseItem::TypeGraph) {
			IGraphStmt *g = elaborate_graph(static_cast<Graph *>((*it)));
			a->setGraph(g);
		} else {
			c = elaborate_struct_action_body_item(*it);

			if (c) {
				a->add(c);
			} else {
				fprintf(stdout, "Error: failed to build action child item %s\n",
						BaseItem::toString((*it)->getObjectType()));
			}
		}
	}


	return a;
}

IBind *Elaborator::elaborate_bind(Bind *b) {
	const std::vector<BaseItem *> &items = b->getItems();
	std::vector<IBaseItem *> items_psi;

	// TODO: must map BaseItem references to PSI references
	// What this really means is converting the BaseItem references to expressions

	return m_model->mkBind(items_psi);
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
		} else {
			// TODO:
			fprintf(stdout, "Error: Unknown component body item %s\n",
					BaseItem::toString(t->getObjectType()));
		}
	}

	return comp;
}

// TODO: should return
IConstraint *Elaborator::elaborate_constraint(Constraint *c) {
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
}

IBaseItem *Elaborator::elaborate_struct_action_body_item(BaseItem *t) {
	IBaseItem *ret = 0;

	if (t->getObjectType() == BaseItem::TypeConstraint) {
		ret = elaborate_constraint(static_cast<Constraint *>(t));
	} else if (t->getObjectType() == BaseItem::TypeField) {
		FieldItem *f = static_cast<FieldItem *>(t);
		BaseItem *dt = f->getDataType();
		IField::FieldAttr attr = getAttr(f);

		if (dt->getObjectType() == BaseItem::TypeBit) {
			// This is a bit-type field
			BitType *bt = static_cast<BitType *>(dt);
			IScalarType *field_t = m_model->mkScalarType(
					IScalarType::ScalarType_Bit, bt->getMsb(), bt->getLsb());
			ret = m_model->mkField(f->getName(), field_t, attr);
		} else if (dt->getObjectType() == BaseItem::TypeInt) {
			// This is an int-type field
			IntType *it = static_cast<IntType *>(dt);
			IScalarType *field_t = m_model->mkScalarType(
					IScalarType::ScalarType_Int, it->getMsb(), it->getLsb());
			ret = m_model->mkField(f->getName(), field_t, attr);
		} else if (dt->getObjectType() == BaseItem::TypeBool) {
			// Boolean field
			Bool *it = static_cast<Bool *>(dt);

			IScalarType *field_t = m_model->mkScalarType(
					IScalarType::ScalarType_Bool, 0, 0);
			ret = m_model->mkField(f->getName(), field_t, attr);
		} else if (dt->getObjectType() == BaseItem::TypeChandle) {
			Chandle *it = static_cast<Chandle *>(dt);
			IScalarType *field_t = m_model->mkScalarType(
					IScalarType::ScalarType_Chandle, 0, 0);
			ret = m_model->mkField(f->getName(), field_t, attr);
		} else if (dt->getObjectType() == BaseItem::TypeAction) {
			// This is an action-type field
			IBaseItem *action_t = find_type_decl(dt);
			ret = m_model->mkField(f->getName(), action_t, attr);
		} else if (dt->getObjectType() == BaseItem::TypeStruct) {
			// This is an struct-type field
			IBaseItem *struct_t = find_type_decl(dt);
			ret = m_model->mkField(f->getName(), struct_t, attr);
		} else {
			// Error
		}
	} else if (t->getObjectType() == BaseItem::TypeExec) {
		// TODO:
	} else {
		// TODO: See if this is a field

	}

	return ret;
}

IFieldRef *Elaborator::elaborate_field_ref(BaseItem *t) {
	std::vector<NamedBaseItem *>	types;
	std::vector<IField *> 			fields;

	while (t) {
		// Traverse up to the point where we find the
		// declaration scope that contains this expression
		if (t == m_class_expr_ctxt) {
			// TODO: might need to do something different for extended types?
			break;
		} else {
			NamedBaseItem *ni = toNamedItem(t);

			if (ni) {
				types.push_back(ni);
			}
		}
		t = t->getParent();
	}

	IScopeItem *scope = toScopeItem(m_model_expr_ctxt);
	if (scope) {
		for (int32_t i=types.size()-1; i>=0; i--) {
			NamedBaseItem *t = types.at(i);
			IBaseItem *t_it = 0;

			for (std::vector<IBaseItem *>::const_iterator s_it=scope->getItems().begin();
					s_it!=scope->getItems().end(); s_it++) {
				if ((*s_it)->getType() == IBaseItem::TypeField &&
						static_cast<IField *>(*s_it)->getName() == t->getName()) {
					t_it = *s_it;
					break;
				}
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

	return m_model->mkFieldRef(fields);
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
		IGraphRepeatStmt::RepeatType type = IGraphRepeatStmt::RepeatType_Forever;

		// TODO: must handle other types
		IExpr *cond = 0;
		IGraphStmt *body;
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
	NamedBaseItem *ni = toNamedItem(item);

	if (!ni || ni->getName() == "" || type_h.size() == 1) {
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
	}
	return 0;
}

NamedBaseItem *Elaborator::toNamedItem(BaseItem *it) {
	return NamedBaseItem::to(it);

}

void Elaborator::error(const std::string &msg) {
	fprintf(stdout, "Error: %s\n", msg.c_str());
}

} /* namespace psi */
