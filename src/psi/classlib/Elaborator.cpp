/*
 * PsiElaborator.cpp
 *
 *  Created on: May 2, 2016
 *      Author: ballance
 */

#include "classlib/Elaborator.h"
#include "api/IComponent.h"
#include "classlib/ExprCoreList.h"

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
			elaborate_struct(model->getGlobalPackage(), static_cast<Struct *>(t));
		}
	}

	// Next, go through and declare global scopes
	for (it=root->getChildren().begin(); it!=root->getChildren().end(); it++) {
		Type *t = (*it);

		if (t->getObjectType() == Type::TypePackage) {
			elaborate_package(model, static_cast<Package *>(t));
		} else if (t->getObjectType() == Type::TypeComponent) {
			elaborate_component(static_cast<Component *>(t));
		} else if (t->getObjectType() != Type::TypeStruct) {
			// Error:
			error(std::string("Unsupported root element: ") +
					Type::toString(t->getObjectType()));
		}
	}
}

IAction *Elaborator::elaborate_action(Action *c) {
	IAction *a = 0;

	return a;
}

void Elaborator::elaborate_component(Component *c) {
	IComponent *comp = m_model->mkComponent(c->getName());

	std::vector<Type *>::const_iterator it = c->getChildren().begin();

	for (; it!=c->getChildren().end(); it++) {
		Type *t = *it;

		if (t->getObjectType() == Type::TypeAction) {
			IAction *a = elaborate_action(static_cast<Action *>(t));
//			comp->add(a);
		} else {
			// TODO:
		}
	}

	m_model->add(comp);
}

// TODO: should return
void Elaborator::elaborate_constraint(Constraint *c) {
	Expr &e = c->getStmt();

	if (e.getOp() != Expr::List) {
		// Something is wrong here
		fprintf(stdout, "Internal Error: Expecting ExprList\n");
	}

	ExprCoreList *l = static_cast<ExprCoreList *>(e.getCore().ptr());
	std::vector<SharedPtr<ExprCore> >::const_iterator it = l->getExprList().begin();

	for (; it!=l->getExprList().end(); it++) {
		ExprCore *ec = it->ptr();

		elaborate_constraint_stmt(ec);

	}
}

void Elaborator::elaborate_constraint_if(ExprCoreIf *if_c) {
	fprintf(stdout, "elaborate_constraint_if: %p\n", if_c);

	elaborate_expr(if_c->getCond().getCorePtr());

	elaborate_constraint_stmt(if_c->getTrue().getCorePtr());

	if (if_c->getFalse().getCorePtr()) {
		elaborate_constraint_stmt(if_c->getFalse().getCorePtr());
	}
}

void Elaborator::elaborate_constraint_stmt(ExprCore *s) {
	if (s->getOp() == Expr::Stmt_If || s->getOp() == Expr::Stmt_IfElse) {
		elaborate_constraint_if(static_cast<ExprCoreIf *>(s));
	} else if (Expr::isBinOp(s->getOp())) {
		elaborate_expr(s);
	} else if (s->getOp() == Expr::List) {
		ExprCoreList *l = static_cast<ExprCoreList *>(s);
		std::vector<SharedPtr<ExprCore> >::const_iterator it = l->getExprList().begin();
		for (; it!=l->getExprList().end(); it++) {
			elaborate_constraint_stmt(it->ptr());
		}
	} else {
		// Don't really know what's going on
		fprintf(stdout, "Error: unknown constraint statement %s\n",
				Expr::toString(s->getOp()));
	}
}

IExpr *Elaborator::elaborate_expr(ExprCore *e) {
	fprintf(stdout, "expr: %s\n", Expr::toString(e->getOp()));

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
	default:
		fprintf(stdout, "Error: unkown expression %s\n",
				Expr::toString(e->getOp()));
	}

	return ret;
}

void Elaborator::elaborate_struct(IPackage *pkg, Struct *str) {
	IStruct::StructType t = IStruct::Base; // TODO:
	IStruct *super_type = 0; // TODO:
	IStruct *s = m_model->mkStruct(str->getName(), t, super_type);

	std::vector<Type *>::const_iterator it = str->getChildren().begin();

	for (; it!=str->getChildren().end(); it++) {
		Type *t = *it;

		fprintf(stdout, "ObjectType: %s\n", Type::toString(t->getObjectType()));

		if (t->getObjectType() == Type::TypeConstraint) {
			elaborate_constraint(static_cast<Constraint *>(t));
		}
	}

	pkg->add(s);
}

void Elaborator::elaborate_package(IModel *model, Package *pkg_cl) {
	IPackage *pkg = model->findPackage(pkg_cl->getName());

	if (pkg) {
		error("Multiple declaration of package " + pkg_cl->getName());
		return;
	}

	pkg = model->findPackage(pkg_cl->getName(), true);
}

void Elaborator::error(const std::string &msg) {
	fprintf(stdout, "Error: %s\n", msg.c_str());
}

} /* namespace psi */
