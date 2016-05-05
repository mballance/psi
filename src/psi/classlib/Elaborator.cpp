/*
 * PsiElaborator.cpp
 *
 *  Created on: May 2, 2016
 *      Author: ballance
 */

#include "classlib/Elaborator.h"
#include "api/IComponent.h"
#include "classlib/ExprCoreList.h"
#include "classlib/BitType.h"
#include "classlib/IntType.h"

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
			IComponent *c = elaborate_component(static_cast<Component *>(t));
			m_model->add(c);
		} else if (t->getObjectType() != Type::TypeStruct) {
			// Error:
			error(std::string("Unsupported root element: ") +
					Type::toString(t->getObjectType()));
		}
	}
}

IAction *Elaborator::elaborate_action(Action *c) {
	IAction *super_a = 0; // TODO:
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

IComponent *Elaborator::elaborate_component(Component *c) {
	IComponent *comp = m_model->mkComponent(c->getName());

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
	fprintf(stdout, "elaborate_constraint_if: %p\n", if_c);

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
	IStruct *super_type = 0; // TODO:
	IStruct *s = m_model->mkStruct(str->getName(), t, super_type);

	std::vector<Type *>::const_iterator it = str->getChildren().begin();

	for (; it!=str->getChildren().end(); it++) {
		IBaseItem *api_it = elaborate_struct_action_body_item(*it);

		if (api_it) {
			s->add(api_it);
		} else {
			fprintf(stdout, "Error: failed to elaborate struct item: %s\n",
					Type::toString((*it)->getObjectType()));
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
		IField::FieldAttr attr = IField::FieldAttr_None;
		if (bt->isRand()) {
			attr = IField::FieldAttr_Rand;
		} else if (bt->isInput()) {
			attr = IField::FieldAttr_Input;
		} else if (bt->isOutput()) {
			attr = IField::FieldAttr_Output;
		}
		IBitType *field_t = m_model->mkBitType(bt->getMsb(), bt->getLsb());
		ret = m_model->mkField(bt->getName(), field_t, attr);
	} else if (t->getObjectType() == Type::TypeInt) {
		// This is an int-type field
		IntType *it = static_cast<IntType *>(t);
		IField::FieldAttr attr = IField::FieldAttr_None;
		if (it->isRand()) {
			attr = IField::FieldAttr_Rand;
		} else if (it->isInput()) {
			attr = IField::FieldAttr_Input;
		} else if (it->isOutput()) {
			attr = IField::FieldAttr_Output;
		}
		IIntType *field_t = m_model->mkIntType(it->getMsb(), it->getLsb());
		ret = m_model->mkField(it->getName(), field_t, attr);
	} else if (t->getObjectType() == Type::TypeAction) {
		// This is an action-type field

	} else if (t->getObjectType() == Type::TypeStruct) {
		// This is an struct-type field

	} else if (t->getObjectType() == Type::TypeExec) {
		// TODO:
	} else {
		// See if this is a field

	}

	return ret;
}

void Elaborator::error(const std::string &msg) {
	fprintf(stdout, "Error: %s\n", msg.c_str());
}

} /* namespace psi */
