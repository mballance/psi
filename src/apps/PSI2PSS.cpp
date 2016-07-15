/*
 * PSI2PSS.cpp
 *
 *  Created on: Jul 15, 2016
 *      Author: ballance
 */

#include "PSI2PSS.h"
#include <stdio.h>

namespace psi {
namespace apps {

PSI2PSS::PSI2PSS() {
	// TODO Auto-generated constructor stub

}

PSI2PSS::~PSI2PSS() {
	// TODO Auto-generated destructor stub
}

void PSI2PSS::visit_model(IModel *model) {
	PSI2StringProcessor::visit_model(model);
}

void PSI2PSS::visit_package(IPackage *pkg) {
	if (pkg->getName() != "") {
		println(std::string("package ") + pkg->getName() + " {");
		inc_indent();
	}

	PSI2StringProcessor::visit_package(pkg);

	if (pkg->getName() != "") {
		dec_indent();
		println("}");
	}
}

void PSI2PSS::visit_action(IAction *a) {
	std::string t = "action ";
	t += a->getName();

	if (a->getSuperType()) {
		t += " : " + a->getSuperType()->getName();
	}

	t += " {";
	println(t);

	inc_indent();
	PSI2StringProcessor::visit_action(a);
	dec_indent();

	println("}");
}

void PSI2PSS::visit_bind(IBind *b) {
	// TODO:

}

void PSI2PSS::visit_body(IBaseItem *p, const std::vector<IBaseItem *> &items) {
	PSI2StringProcessor::visit_body(p, items);
}

void PSI2PSS::visit_struct(IStruct *s) {
	std::string t = "struct ";
	t += s->getName();

	if (s->getSuperType()) {
		t += " : " + s->getSuperType()->getName();
	}

	t += " {";
	println(t);

	inc_indent();

	PSI2StringProcessor::visit_struct(s);

	dec_indent();

	println("}");
}

void PSI2PSS::visit_component(IComponent *c) {
	std::string t = "component ";
	t += c->getName();

//	if (c->getSuperType()) {
//		t += " : " + c->getSuperType()->getName();
//	}

	t += " {";
	println(t);

	inc_indent();
	PSI2StringProcessor::visit_component(c);
	dec_indent();

	println("}");
}

void PSI2PSS::visit_comp_pkg_body(const std::vector<IBaseItem *> &items) {
	PSI2StringProcessor::visit_comp_pkg_body(items);
}

void PSI2PSS::visit_constraint(IConstraintBlock *c) {
	std::string t = "constraint ";

	if (c->getName() != "") {
		t += c->getName();
		t += " ";
	}

	t += "{";

	println(t);

	inc_indent();
	PSI2StringProcessor::visit_constraint(c);
	dec_indent();

	println("}");
}

void PSI2PSS::visit_constraint_stmt(IConstraint *c) {
	PSI2StringProcessor::visit_constraint_stmt(c);
}

void PSI2PSS::visit_constraint_expr_stmt(IConstraintExpr *c) {
	print(get_indent());
	PSI2StringProcessor::visit_constraint_expr_stmt(c);
	print(";\n");
}

void PSI2PSS::visit_constraint_block(IConstraintBlock *block) {

	println("{");
	inc_indent();
	PSI2StringProcessor::visit_constraint_block(block);
	dec_indent();
	println("}");
}

void PSI2PSS::visit_expr(IExpr *e) {
	PSI2StringProcessor::visit_expr(e);
}

void PSI2PSS::visit_binary_expr(IBinaryExpr *be) {
	if (be->getBinOpType() == IBinaryExpr::BinOp_ArrayRef) {
		visit_expr(be->getLHS());
		print("[");
		visit_expr(be->getRHS());
		print("]");
	} else {
		visit_expr(be->getLHS());
		print(" ");
		print(binop_tostring(be->getBinOpType()));
		print(" ");
		visit_expr(be->getRHS());
	}
}

void PSI2PSS::visit_fieldref_expr(IFieldRef *ref) {
	print(path2string(ref));
}

void PSI2PSS::visit_literal_expr(ILiteral *l) {
	char val[64];
	switch (l->getLiteralType()) {
	case ILiteral::LiteralBit: {
		sprintf(val, "0x%llx", (long long)l->getBit());
		print(val);
	} break;

	case ILiteral::LiteralInt: {
		sprintf(val, "%lld", l->getInt());
		print(val);
	} break;

	case ILiteral::LiteralBool: {
		print((l->getBool())?"true":"false");
	} break;
	}

}

void PSI2PSS::visit_field(IField *f) {
	std::string str = get_field_qualifiers(f);

	if (str != "") {
		str += " ";
	}

	str += get_field_typename(f);
	str += " ";
	str += f->getName();
	str += ";";

	println(str);
}

void PSI2PSS::visit_graph(IGraphStmt *graph) {
	println("graph {");
	inc_indent();
	PSI2StringProcessor::visit_graph(graph);
	dec_indent();
	println("}");
}

void PSI2PSS::visit_graph_stmt(IGraphStmt *stmt) {
	std::string post;

	switch (stmt->getStmtType()) {
	case IGraphStmt::GraphStmt_Block: {
		println("{");
		inc_indent();
		post = "}";
	} break;

	case IGraphStmt::GraphStmt_IfElse: {

	} break;

	case IGraphStmt::GraphStmt_Parallel: {
		println("parallel {");
		inc_indent();
		post = "}";
	} break;

	case IGraphStmt::GraphStmt_Repeat: {
		IGraphRepeatStmt *r = static_cast<IGraphRepeatStmt *>(stmt);

		if (r->getCond()) {
			print(get_indent());
			print("repeat (");
			visit_expr(r->getCond());
			print(") {\n");

		} else {
			// Forever loop
			print(get_indent());
			print("repeat {\n");
		}

		inc_indent();
		if (r->getBody()->getStmtType() == IGraphStmt::GraphStmt_Block) {
			// Expand inline
			IGraphBlockStmt *b = static_cast<IGraphBlockStmt *>(r->getBody());
			for (std::vector<IGraphStmt *>::const_iterator it=b->getStmts().begin();
					it!=b->getStmts().end(); it++) {
				visit_graph_stmt(*it);
			}
		} else {
			visit_graph_stmt(r->getBody());
		}
		dec_indent();
		println("}");
	} break;

	case IGraphStmt::GraphStmt_Schedule: {
		println("schedule {");
		inc_indent();
		post = "}";
	} break;

	case IGraphStmt::GraphStmt_Select: {
		println("select {");
		inc_indent();
		post = "}";
	} break;

	case IGraphStmt::GraphStmt_Traverse: {
		IGraphTraverseStmt *t = static_cast<IGraphTraverseStmt *>(stmt);
		std::string s = path2string(t->getAction()->getFieldPath());

		if (t->getWith()) {
			s += " with ";
			print(get_indent());
			print(s);

			if (t->getWith()->getConstraintType() == IConstraint::ConstraintType_Block) {
				IConstraintBlock *b = static_cast<IConstraintBlock *>(t->getWith());
				print("{\n");
				inc_indent();
				for (std::vector<IConstraint *>::const_iterator it=b->getConstraints().begin();
						it!=b->getConstraints().end(); it++) {
					visit_constraint_stmt(*it);
				}
				dec_indent();
				print(get_indent() + "};\n");
			} else {
				fprintf(stdout, "Error: expect with constraint to be a block\n");
			}
		} else {
			s += ";";
			println(s);
		}

	} break;
	}

	if (post != "") {
		PSI2StringProcessor::visit_graph_stmt(stmt);
		dec_indent();
		println(post);
	}
}

void PSI2PSS::visit_graph_block_stmt(IGraphBlockStmt *block) {

}

std::string PSI2PSS::get_field_typename(IField *f) {
	char msb_s[64], lsb_s[64];
	std::string ret;
	IBaseItem *dt_i = f->getDataType();

	if (dt_i) {
		if (dt_i->getType() == IBaseItem::TypeScalar) {
			IScalarType *st = static_cast<IScalarType *>(dt_i);
			std::string tname = "unknown-scalar";
			sprintf(msb_s, "%d", st->getMSB());
			sprintf(lsb_s, "%d", st->getLSB());
			bool has_bitwidth = false;

			if (st->getScalarType() == IScalarType::ScalarType_Bit) {
				tname = "bit";
				has_bitwidth = true;
			} else if (st->getScalarType() == IScalarType::ScalarType_Int) {
				tname = "int";
				has_bitwidth = true;
			} else if (st->getScalarType() == IScalarType::ScalarType_Bool) {
				tname = "bool";
				has_bitwidth = false;
			}

			if (has_bitwidth) {
				ret = tname + "[" + msb_s + ":" + lsb_s + "]";
			} else {
				ret = tname;
			}
		} else if (dt_i->getType() == IBaseItem::TypeAction ||
				dt_i->getType() == IBaseItem::TypeStruct ||
				dt_i->getType() == IBaseItem::TypeComponent) {
			ret = type2string(dt_i);
		} else {
			ret = "unknown-type";
		}
	} else {
		ret = "null-type";
	}

	return ret;
}

std::string PSI2PSS::binop_tostring(IBinaryExpr::BinOpType t) {
	switch (t) {
	case IBinaryExpr::BinOp_Eq: return "=";
	case IBinaryExpr::BinOp_EqEq: return "==";
	case IBinaryExpr::BinOp_NotEq: return "!=";
	case IBinaryExpr::BinOp_GE: return ">=";
	case IBinaryExpr::BinOp_GT: return ">";
	case IBinaryExpr::BinOp_LE: return "<=";
	case IBinaryExpr::BinOp_LT: return "<";
	case IBinaryExpr::BinOp_And: return "&";
	case IBinaryExpr::BinOp_AndAnd: return "&&";
	case IBinaryExpr::BinOp_Or: return "|";
	case IBinaryExpr::BinOp_OrOr: return "||";
	case IBinaryExpr::BinOp_Minus: return "-";
	case IBinaryExpr::BinOp_Plus: return "+";
	case IBinaryExpr::BinOp_Multiply: return "*";
	case IBinaryExpr::BinOp_Divide: return "/";
	case IBinaryExpr::BinOp_Mod: return "%";
	}

	return "UNKNOWN_OP";
}

} /* namespace apps */
} /* namespace psi */
