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
#include "classlib/IntType.h"
#include "classlib/Bool.h"

#include <stdio.h>

namespace psi {

using namespace std;

Elaborator::Elaborator() : m_model(0) {
	// TODO Auto-generated constructor stub

}

Elaborator::~Elaborator() {
	// TODO Auto-generated destructor stub
}

void Elaborator::elaborate(Type *root, IModel *model) {
	vector<Type *>::const_iterator it;

	m_model = model;

	// First, go through and declare global data types
	for (it=root->getChildren().begin(); it!=root->getChildren().end(); it++) {
		Type *t = (*it);

		if (t->getObjectType() == Type::TypeStruct) {
			IStruct *s = elaborate_struct(static_cast<Struct *>(t));
			m_model->getGlobalPackage()->add(s);
		}
	}

	// Next, go through and declare global scopes
	for (it=root->getChildren().begin(); it!=root->getChildren().end(); it++) {
		Type *t = (*it);

		if (t->getObjectType() == Type::TypePackage) {
			elaborate_package(model, static_cast<Package *>(t));
		} else if (t->getObjectType() == Type::TypeComponent) {
			IComponent *c = elaborate_component(m_model, static_cast<Component *>(t));
			fprintf(stdout, "elaborate component: %s\n", c->getName().c_str());
//			m_model->add(c);
		} else if (t->getObjectType() != Type::TypeStruct) {
			// Error:
			error(std::string("Unsupported root element: ") +
					Type::toString(t->getObjectType()));
		}
	}
}

IAction *Elaborator::elaborate_action(Action *c) {
	IAction *super_a = 0; // TODO:

	if (c->getSuperType()) {
		// Locate the type
		IBaseItem *t = find_type_decl(c->getSuperType());

		if (t->getType() == IBaseItem::TypeAction) {
			super_a = static_cast<IAction *>(t);
		}

		// TODO: error handling
	}
	IAction *a = m_model->mkAction(c->getName(), super_a);

	std::vector<Type *>::const_iterator it=c->getChildren().begin();

	for (; it!=c->getChildren().end(); it++) {
		IBaseItem *c = elaborate_struct_action_body_item(*it);

		if (c) {
			a->add(c);
		} else {
			fprintf(stdout, "Error: failed to build action child item %s\n",
					Type::toString((*it)->getObjectType()));
		}
	}


	return a;
}

IComponent *Elaborator::elaborate_component(IScopeItem *scope, Component *c) {
	IComponent *comp = m_model->mkComponent(c->getName());
	if (scope) {
		scope->add(comp);
	}

	std::vector<Type *>::const_iterator it = c->getChildren().begin();

	for (; it!=c->getChildren().end(); it++) {
		Type *t = *it;

		if (t->getObjectType() == Type::TypeAction) {
			IAction *a = elaborate_action(static_cast<Action *>(t));
			comp->add(a);
		} else if (t->getObjectType() == Type::TypeStruct) {
			IStruct *s = elaborate_struct(static_cast<Struct *>(t));
			comp->add(s);
		} else {
			// TODO:
			fprintf(stdout, "Error: Unknown component body item %s\n",
					Type::toString(t->getObjectType()));
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
		ret = m_model->mkStringLiteral("typeref");
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
	std::vector<Type *>		type_h;

	if (str->getSuperType()) {
		// Look for the actual type
		IBaseItem *it_b = find_type_decl(str->getSuperType());

		build_type_hierarchy(type_h, str);

		if (!it_b) {
			error(std::string("Failed to find struct type") +
					str->getSuperType()->getName());
		} else {
			if (it_b->getType() == IBaseItem::TypeStruct) {
				super_type = static_cast<IStruct *>(it_b);
			} else {
				error(std::string("Super type ") +
						str->getSuperType()->getName() +
						" is not a struct type");
			}
		}
	}

	IStruct *s = m_model->mkStruct(str->getName(), t, super_type);

	for (uint32_t i=0; i<str->getChildren().size(); i++) {
		Type *t = str->getChildren().at(i);
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
						Type::toString(t->getObjectType()));
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

IBaseItem *Elaborator::elaborate_struct_action_body_item(Type *t) {
	IBaseItem *ret = 0;

	if (t->getObjectType() == Type::TypeConstraint) {
		ret = elaborate_constraint(static_cast<Constraint *>(t));
	} else if (t->getObjectType() == Type::TypeBit) {
		// This is a bit-type field
		BitType *bt = static_cast<BitType *>(t);
		IScalarType *field_t = m_model->mkScalarType(
				IScalarType::ScalarType_Bit, bt->getMsb(), bt->getLsb());
		ret = m_model->mkField(bt->getName(), field_t, getAttr(bt));
	} else if (t->getObjectType() == Type::TypeInt) {
		// This is an int-type field
		IntType *it = static_cast<IntType *>(t);
		IScalarType *field_t = m_model->mkScalarType(
				IScalarType::ScalarType_Int, it->getMsb(), it->getLsb());
		ret = m_model->mkField(it->getName(), field_t, getAttr(it));
	} else if (t->getObjectType() == Type::TypeBool) {
		// Boolean field
		Bool *it = static_cast<Bool *>(t);

		IScalarType *field_t = m_model->mkScalarType(
				IScalarType::ScalarType_Bool, 0, 0);
		ret = m_model->mkField(it->getName(), field_t, getAttr(it));
	} else if (t->getObjectType() == Type::TypeAction) {
		// This is an action-type field

	} else if (t->getObjectType() == Type::TypeStruct) {
		// This is an struct-type field
		Struct *it = static_cast<Struct *>(t);
		IBaseItem *struct_t = find_type_decl(t->getTypeData());

		ret = m_model->mkField(it->getName(), struct_t, getAttr(it));
	} else if (t->getObjectType() == Type::TypeExec) {
		// TODO:
	} else {
		// See if this is a field

	}

	return ret;
}

IField::FieldAttr Elaborator::getAttr(Type *t) {
	IField::FieldAttr attr = IField::FieldAttr_None;
	if (t->isRand()) {
		attr = IField::FieldAttr_Rand;
	} else if (t->isInput()) {
		attr = IField::FieldAttr_Input;
	} else if (t->isOutput()) {
		attr = IField::FieldAttr_Output;
	}

	return attr;
}

IBaseItem *Elaborator::find_type_decl(Type *t) {
	std::vector<Type *> type_p;

	Type *ti = t;
	while (ti) {
		type_p.push_back(ti);
		ti = ti->getParent();
	}

	IScopeItem *s = 0;
	for (int32_t i=type_p.size()-1; i>=0; i--) {
		ti = type_p.at(i);

		if (s) {
			s = find_named_scope(s->getItems(), ti->getName());
		} else if (ti->getObjectType() != Type::TypeRegistry) { // Skip global-scope references
			// global search
			// First, do a global lookup for package and component items
			s = find_named_scope(m_model->getItems(), ti->getName());

			if (!s) {
				s = find_named_scope(
						m_model->getGlobalPackage()->getItems(),
						ti->getName());
			}
		}

		if (!s && ti->getObjectType() != Type::TypeRegistry) {
			error(std::string("Failed to find type ") + ti->getName());
			break;
		}
	}

	return s;
}

IScopeItem *Elaborator::find_named_scope(
		const std::vector<IBaseItem *>			&items,
		const std::string						&name) {
	IScopeItem *ret = 0;
	std::vector<IBaseItem *>::const_iterator it;

	for (it=items.begin(); it!=items.end(); it++) {
		if ((*it)->getType() == IBaseItem::TypeComponent) {
//			fprintf(stdout, "    Component: %s\n", static_cast<IComponent *>(*it)->getName().c_str());
			if (static_cast<IComponent *>(*it)->getName() == name) {
				ret = static_cast<IComponent *>(*it);
				break;
			}
		} else if ((*it)->getType() == IBaseItem::TypeAction) {
//			fprintf(stdout, "    Action: %s\n", static_cast<IAction *>(*it)->getName().c_str());
			if (static_cast<IAction *>(*it)->getName() == name) {
				ret = static_cast<IAction *>(*it);
				break;
			}
		} else if ((*it)->getType() == IBaseItem::TypeStruct) {
//			fprintf(stdout, "    Struct: %s\n", static_cast<IStruct *>(*it)->getName().c_str());
			if (static_cast<IStruct *>(*it)->getName() == name) {
				ret = static_cast<IStruct *>(*it);
				break;
			}
		} else {
            fprintf(stdout, "    Unknown: it=%d\n", (*it)->getType());
		}
	}

	return ret;
}

bool Elaborator::should_filter(
		const std::vector<Type *>	&items,
		uint32_t					i,
		const std::vector<Type *>	&type_h) {
	// Base types are evaluated first
	// - Must preserve 'override' elements
	// - Must filter out re-declarations
	//
	// - Count of a given element in the parent type
	// - Count of a given element in this type
	// -> Preserve if parent count is 0
	// -> Preserve if
	bool ret = false;

	Type *item = items.at(i);
	const std::string &name = items.at(i)->getName();

	if (name == "" || type_h.size() == 1) {
		// Always preserve unnamed items
		return false;
	}

	// Count the occurrences of this item in the parent
	uint32_t parent_c = 0;

	Type *p = type_h.at(1);
	for (std::vector<Type *>::const_iterator it=p->getChildren().begin();
			it != p->getChildren().end(); it++) {
		Type *t = *it;

		if (t->getObjectType() == item->getObjectType() &&
				t->getName() == item->getName()) {
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
			Type *t = items.at(ii);

			if (t->getObjectType() == item->getObjectType() &&
					t->getName() == item->getName()) {
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
		std::vector<Type *>			&items,
		Type						*t) {
	while (t) {
		items.push_back(t);

		if (t->getObjectType() == Type::TypeAction) {
			t = static_cast<Action *>(t)->getSuperType();
		} else if (t->getObjectType() == Type::TypeStruct) {
			t = static_cast<Struct *>(t)->getSuperType();
		} else {
			t = 0;
		}
	}
}

void Elaborator::error(const std::string &msg) {
	fprintf(stdout, "Error: %s\n", msg.c_str());
}

} /* namespace psi */
