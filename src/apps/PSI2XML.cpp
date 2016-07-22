/*
 * PSI2XML.cpp
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
 *  Created on: May 3, 2016
 *      Author: ballance
 */

#include "PSI2XML.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

namespace psi {
namespace apps {

PSI2XML::PSI2XML() : m_ind_incr(4), m_fixed_inline_addr(false) {
	// TODO Auto-generated constructor stub

}

PSI2XML::~PSI2XML() {
	// TODO Auto-generated destructor stub
}

const std::string &PSI2XML::traverse(IModel *model) {
	m_content.clear();

	println("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	enter("model \n"
			"  xmlns:pss=\"http://accellera.org/PSS\"\n"
			"  xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
			"  xsi:schemaLocation=\"http://accellera.org/PSS PSSModel.xsd\"");

	IPackage *pkg = model->getGlobalPackage();
	process_pkg(pkg);

	std::vector<IBaseItem *>::const_iterator it=model->getItems().begin();

	for (; it!=model->getItems().end(); it++) {
		IBaseItem *i = *it;

		if (i->getType() == IBaseItem::TypePackage) {
			IPackage *pkg = static_cast<IPackage *>(i);
			process_pkg(pkg);
		} else if (i->getType() == IBaseItem::TypeComponent) {
			process_component(static_cast<IComponent *>(i));
		} else {
			// Really shouldn't be anything else in the global scope
			error("Unknown global-scope item: %d", i->getType());
		}
	}

	exit("model");

	return m_content;
}

void PSI2XML::process_pkg(IPackage *pkg) {
	if (pkg->getName() == "") {
		enter("package");
	} else {
		enter("package name=\"" + pkg->getName() + "\"");
	}

	std::vector<IBaseItem *>::const_iterator it=pkg->getItems().begin();

	for (; it!=pkg->getItems().end(); it++) {
		IBaseItem *i = *it;

		fprintf(stdout, "pkg_item: %d\n", i->getType());

		switch (i->getType()) {
			case IBaseItem::TypeAction:
				break;

			case IBaseItem::TypeStruct:
				process_struct(static_cast<IStruct *>(i));
				break;

			case IBaseItem::TypeExec:
				process_exec(static_cast<IExec *>(i));
				break;

			default:
				error("Unsupported package item: %d\n", i->getType());
				break;
		}
	}

	exit("package");
}

void PSI2XML::process_action(IAction *a) {
	IAction *super_a = a->getSuperType();

	enter("action name=\"" + a->getName() + "\"");

	if (super_a) {
		type2hierarchical_id(super_a, "super");
	}

	process_body(a->getItems(), "action");

	if (a->getGraph()) {
		process_graph(a->getGraph());
	}

	exit("action");
}

void PSI2XML::process_struct(IStruct *str) {
	IStruct *super_s = 0; // TODO: super-type
	std::string tag = "struct name=\"" + str->getName() + "\"";


	switch (str->getStructType()) {
	case IStruct::Memory: tag += " qualifier=\"memory\""; break;
	case IStruct::Resource: tag += " qualifier=\"resource\""; break;
	case IStruct::Stream: tag += " qualifier=\"stream\""; break;
	case IStruct::State: tag += " qualifier=\"state\""; break;
	}

	enter(tag);

	if (str->getSuperType()) {
		type2hierarchical_id(str->getSuperType(), "super");
	}

	process_body(str->getItems(), "struct");

	exit("struct");
}

void PSI2XML::process_bind(IBind *b) {
	enter("bind");

	for (std::vector<IBindPath *>::const_iterator it=b->getTargets().begin();
			it!=b->getTargets().end(); it++) {
		to_hierarchical_id((*it)->getPath(), "bindpath");
	}

	exit("bind");
}

void PSI2XML::process_body(
		const std::vector<IBaseItem *>  &items,
		const std::string				&ctxt) {
	std::vector<IBaseItem *>::const_iterator it = items.begin();
	std::string field_tag = (ctxt == "struct")?"pss:struct_field_declaration":
			(ctxt == "action")?"pss:action_field_declaration":
			(ctxt == "component")?"pss:component_field_declaration":"pss:unknown_field_declaration";

	for (; it!=items.end(); it++) {
		IBaseItem *i = *it;

		switch (i->getType()) {
		case IBaseItem::TypeBind:
			process_bind(static_cast<IBind *>(i));
			break;

		case IBaseItem::TypeConstraint:
			process_constraint_block(static_cast<IConstraintBlock *>(i));
			break;

		case IBaseItem::TypeAction:
			process_action(static_cast<IAction *>(i));
			break;

		case IBaseItem::TypeField:
			process_field(static_cast<IField *>(i));
			break;

		case IBaseItem::TypeStruct:
			process_struct(static_cast<IStruct *>(i));
			break;

		case IBaseItem::TypeExec:
			process_exec(static_cast<IExec *>(i));
			break;

		default:
			fprintf(stdout, "Error: Unknown body item %d\n", i->getType());
		}
	}
}

void PSI2XML::process_component(IComponent *c) {

	enter(std::string("component name=\"") + c->getName() + "\"");

	// TODO: super type
//	if (c->getSu)

//	process_comp_pkg_body(c->getItems());
	process_body(c->getItems(), "component");

	exit("component");
}

void PSI2XML::process_comp_pkg_body(const std::vector<IBaseItem *> &items) {
	std::vector<IBaseItem *>::const_iterator it=items.begin();

	for (; it!=items.end(); it++) {
		switch ((*it)->getType()) {
			case IBaseItem::TypeAction:
				process_action(static_cast<IAction *>(*it));
				break;

			case IBaseItem::TypeStruct:
				process_struct(static_cast<IStruct *>(*it));
				break;
		}
	}

}

void PSI2XML::process_constraint_set(IConstraint *c, const char *tag) {
	if (tag) {
		enter(tag);
	}

	if (c->getConstraintType() == IConstraint::ConstraintType_Block) {
		IConstraintBlock *b = static_cast<IConstraintBlock *>(c);
		for (std::vector<IConstraint *>::const_iterator it=b->getConstraints().begin();
				it!=b->getConstraints().end(); it++) {
			process_constraint(*it);
		}
	} else {
		process_constraint(c);
	}

	if (tag) {
		exit(tag);
	}
}

void PSI2XML::process_constraint(IConstraint *c) {
	switch (c->getConstraintType()) {
	case IConstraint::ConstraintType_Block: {
		IConstraintBlock *b = static_cast<IConstraintBlock *>(c);
		println("<block>");
		inc_indent();

		for (std::vector<IConstraint *>::const_iterator it=b->getConstraints().begin();
				it!=b->getConstraints().end(); it++) {
			process_constraint(*it);
		}

		dec_indent();
		println("</block>");
	} break;

	case IConstraint::ConstraintType_Expr:
		process_expr(static_cast<IConstraintExpr *>(c)->getExpr(), "stmt");
		break;

	case IConstraint::ConstraintType_If: {
		IConstraintIf *c_if = static_cast<IConstraintIf *>(c);

		enter("if");
		enter("cond");
		process_expr(c_if->getCond());
		exit("cond");

		process_constraint_set(c_if->getTrue(), "true");

		if (c_if->getFalse()) {
			process_constraint_set(c_if->getFalse(), "false");
		}

		exit("if");
		} break;
	}
}

void PSI2XML::process_constraint_block(IConstraintBlock *block) {
	std::vector<IConstraint *>::const_iterator it = block->getConstraints().begin();

	if (block->getName() == "") {
		enter("constraint");
	} else {
		enter("constraint name=\"" + block->getName() + "\"");
	}

	for (; it!=block->getConstraints().end(); it++) {
		IConstraint *c = *it;
		process_constraint(c);
	}

	exit("constraint");
}

void PSI2XML::process_exec(IExec *exec) {
	std::string kind_s = "UNKNOWN";

	enter("exec");

	switch (exec->getExecKind()) {
	case IExec::Declaration: kind_s = "declaration"; break;
	case IExec::PreSolve: kind_s = "pre_solve"; break;
	case IExec::PostSolve: kind_s = "post_solve"; break;
	case IExec::Body: kind_s = "body"; break;
	}

	switch (exec->getExecType()) {
	case IExec::Native: {
	} break;

	case IExec::TargetTemplate: {
	} break;

	case IExec::Inline: {
		std::string addr_s;
		char tmp[64];

		if (m_fixed_inline_addr) {
			addr_s = "0xDEADBEEFDEADBEEF";
		} else {
			sprintf(tmp, "%p", exec->getInlineExec());
			addr_s = tmp;
		}

		println("<pss:inline kind=\"" + kind_s + "\" address=\"" + addr_s + "\"/>");
	} break;
	}

	exit("exec");
}

void PSI2XML::process_expr(IExpr *e, const char *tag) {
	if (!e) {
		fprintf(stdout, "Error: null expression\n");
		return;
	}
	if (tag) {
		enter(tag);
	}
	switch (e->getType()) {
		case IExpr::ExprType_BinOp: {
			IBinaryExpr *be = static_cast<IBinaryExpr *>(e);
			std::string op = "<unknown>";
			switch (be->getBinOpType()) {
			case IBinaryExpr::BinOp_EqEq: op = "EqEq"; break;
			case IBinaryExpr::BinOp_NotEq: op = "NotEq"; break;
			case IBinaryExpr::BinOp_GE: op = "GE"; break;
			case IBinaryExpr::BinOp_GT: op = "GT"; break;
			case IBinaryExpr::BinOp_LE: op = "LE"; break;
			case IBinaryExpr::BinOp_LT: op = "LT"; break;
			case IBinaryExpr::BinOp_And: op = "And"; break;
			case IBinaryExpr::BinOp_AndAnd: op = "AndAnd"; break;
			case IBinaryExpr::BinOp_Or: op = "Or"; break;
			case IBinaryExpr::BinOp_OrOr: op = "OrOr"; break;
			case IBinaryExpr::BinOp_Minus: op = "Minus"; break;
			case IBinaryExpr::BinOp_Plus: op = "Plus"; break;
			case IBinaryExpr::BinOp_Multiply: op = "Mul"; break;
			case IBinaryExpr::BinOp_Divide: op = "Div"; break;
			case IBinaryExpr::BinOp_Mod: op = "Mod"; break;
			case IBinaryExpr::BinOp_ArrayRef: op = "ArrRef"; break;
			}
			enter("binexp op=\"" + op + "\"");
			process_expr(be->getLHS(), "lhs");
			process_expr(be->getRHS(), "rhs");
			exit("binexp");
			} break;

		case IExpr::ExprType_Literal: {
			ILiteral *l = static_cast<ILiteral *>(e);
			std::string tag;
			char val[64];

			switch (l->getLiteralType()) {
			case ILiteral::LiteralBit: {
				sprintf(val, "0x%llx", (long long)l->getBit());
			} break;
			case ILiteral::LiteralInt: {
				sprintf(val, "0x%llx", (long long)l->getInt());
			} break;
			case ILiteral::LiteralBool: {
				if (l->getBool()) {
					strcpy(val, "true");
				} else {
					strcpy(val, "false");
				}
			} break;
			default:
				strcpy(val, "UNKNOWN");
			}

			tag = "<pss:number>";
			tag += val;
			tag += "</pss:number>";

			println(tag);

			} break;

		case IExpr::ExprType_FieldRef: {
			const std::vector<IField *> &fields =
					static_cast<IFieldRef *>(e)->getFieldPath();

			enter("ref");

			for (uint32_t i=0; i<fields.size(); i++) {
				IField *field = fields.at(i);
				println(std::string("<pss:path>") + field->getName() + "</pss:path>");
			}
			exit("ref");
			} break;
	}
	if (tag) {
		exit(tag);
	}
}

void PSI2XML::process_field(IField *f) {
	char msb_s[64], lsb_s[64];
	std::string tag = std::string("<pss:field name=\"") + f->getName() + "\"";

	switch (f->getAttr()) {
	case IField::FieldAttr_Rand:
		tag += " qualifier=\"rand\"";
		break;
	case IField::FieldAttr_Input:
		tag += " qualifier=\"input\"";
		break;
	case IField::FieldAttr_Output:
		tag += " qualifier=\"output\"";
		break;
	case IField::FieldAttr_Lock:
		tag += " qualifier=\"lock\"";
		break;
	case IField::FieldAttr_Share:
		tag += " qualifier=\"share\"";
		break;
	case IField::FieldAttr_Pool:
		tag += " qualifier=\"pool\"";
		break;
	}

	tag += ">";
	println(tag);

	inc_indent();

	type2data_type(f->getDataType());

	dec_indent();

	println("</pss:field>");
}

void PSI2XML::process_graph(IGraphStmt *graph) {
	std::vector<IGraphStmt *>::const_iterator it;

	enter("graph");

	process_graph_stmt(graph);

	exit("graph");
}

void PSI2XML::process_graph_stmt(IGraphStmt *stmt, const char *tag) {

	if (tag) {
		enter(tag);
	}

	switch (stmt->getStmtType()) {
	case IGraphStmt::GraphStmt_Block: {
		process_graph_block_stmt(static_cast<IGraphBlockStmt *>(stmt));
	} break;

	case IGraphStmt::GraphStmt_IfElse: {
		fprintf(stdout, "TODO: GraphStmt_IfElse\n");
	} break;

	case IGraphStmt::GraphStmt_Parallel: {
		IGraphBlockStmt *block = static_cast<IGraphBlockStmt *>(stmt);
		enter("parallel");

		for (std::vector<IGraphStmt *>::const_iterator it=block->getStmts().begin();
				it!=block->getStmts().end(); it++) {
			process_graph_stmt(*it, "production");
		}

		exit("parallel");
	} break;

	case IGraphStmt::GraphStmt_Schedule: {
		process_graph_block_stmt(static_cast<IGraphBlockStmt *>(stmt), "schedule");
	} break;

	case IGraphStmt::GraphStmt_Select: {
		IGraphBlockStmt *block = static_cast<IGraphBlockStmt *>(stmt);
		enter("select");

		for (std::vector<IGraphStmt *>::const_iterator it=block->getStmts().begin();
				it!=block->getStmts().end(); it++) {
			process_graph_stmt(*it, "choice");
		}

		exit("select");
	} break;

	case IGraphStmt::GraphStmt_Repeat: {
		IGraphRepeatStmt *r = static_cast<IGraphRepeatStmt *>(stmt);

		std::string tag = "repeat type=\"";
		switch (r->getRepeatType()) {
			case IGraphRepeatStmt::RepeatType_Count: tag += "count"; break;
			case IGraphRepeatStmt::RepeatType_Forever: tag += "forever"; break;
			case IGraphRepeatStmt::RepeatType_While: tag += "while"; break;
			case IGraphRepeatStmt::RepeatType_Until: tag += "until"; break;
		}
		tag += "\"";
		enter(tag);

		if (r->getRepeatType() != IGraphRepeatStmt::RepeatType_Forever) {
			process_expr(r->getCond(), "expr");
		}

		process_graph_stmt(r->getBody(), "body");

		exit("repeat");
	} break;

	case IGraphStmt::GraphStmt_Traverse: {
		IGraphTraverseStmt *t = static_cast<IGraphTraverseStmt *>(stmt);

		std::string tag = "traverse name=\"";
		tag += path2string(t->getAction());
		tag += "\"";


		if (t->getWith()) {
			enter(tag);
			process_constraint_set(t->getWith(), "with");
			exit("traverse");
		} else {
			println("<pss:" + tag + "/>");
		}

	} break;

	default: fprintf(stdout, "TODO: handle graph stmt %d\n", stmt->getStmtType());

	}

	if (tag) {
		exit(tag);
	}
}

void PSI2XML::process_graph_block_stmt(IGraphBlockStmt *block, const char *tag) {
	std::vector<IGraphStmt *>::const_iterator it;

	if (tag) {
		enter(tag);
	}

	for (it=block->getStmts().begin(); it!=block->getStmts().end(); it++) {
		process_graph_stmt(*it);
	}

	if (tag) {
		exit(tag);
	}
}

std::string PSI2XML::type2string(IBaseItem *it) {
	std::string ret;

	while (it) {
		INamedItem *ni = toNamedItem(it);

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

void PSI2XML::type2hierarchical_id(IBaseItem *it, const std::string &tag) {
	std::vector<INamedItem *> p;

	enter(tag);

	while (it) {
		INamedItem *ni = toNamedItem(it);

		if (ni) {
			p.insert(p.begin(), ni);
		} else {
			break;
		}

		it = it->getParent();
	}

	for (std::vector<INamedItem *>::const_iterator it=p.begin();
			it!=p.end(); it++) {
		println("<pss:path>" + (*it)->getName() + "</pss:path>");
	}

	exit(tag);
}

void PSI2XML::type2data_type(IBaseItem *dt_i, const std::string &tag) {
	char msb_s[64], lsb_s[64];

	println("<" + tag + ">");
	inc_indent();

	if (dt_i) {
		if (dt_i->getType() == IBaseItem::TypeScalar) {
			IScalarType *st = static_cast<IScalarType *>(dt_i);
			std::string tname = "pss:unknown-scalar";
			// TODO: this really should be a sub-expression
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
			} else if (st->getScalarType() == IScalarType::ScalarType_Chandle) {
				tname = "chandle";
				has_bitwidth = false;
			} else if (st->getScalarType() == IScalarType::ScalarType_String) {
				tname = "string";
				has_bitwidth = "false";
			}

			if (has_bitwidth) {
				enter(tname);
				enter("msb");
				println(std::string("<pss:number>") + msb_s + "</pss:number>");
				exit("msb");

				enter("lsb");
				println(std::string("<pss:number>") + lsb_s + "</pss:number>");
				exit("lsb");

				exit(tname);
			} else {
				println(std::string("<pss:") + tname + "/>");
			}
		} else if (dt_i->getType() == IBaseItem::TypeAction ||
				dt_i->getType() == IBaseItem::TypeStruct ||
				dt_i->getType() == IBaseItem::TypeComponent) {
			type2hierarchical_id(dt_i, "user");
		} else {
			println("<pss:unknown-type/>");
		}
	} else {
		println("<pss:null-type/>");
	}

	dec_indent();
	println("</" + tag + ">");
}

void PSI2XML::to_hierarchical_id(const std::vector<IBaseItem *> &path, const char *tag) {
	if (tag) {
		enter(tag);
	}

	for (std::vector<IBaseItem *>::const_iterator it=path.begin();
			it!=path.end(); it++) {
		INamedItem *named_it = toNamedItem(*it);
		if (named_it) {
			println(std::string("<pss:path>") + named_it->getName() + "</pss:path>");
		} else {
			println("<pss:path>UNNAMED</pss:path>");
		}
	}

	if (tag) {
		exit(tag);
	}
}

std::string PSI2XML::path2string(IFieldRef *f) {
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

void PSI2XML::enter(const std::string &t) {
	println(std::string("<pss:" + t + ">"));
	inc_indent();
}

void PSI2XML::exit(const std::string &t) {
	dec_indent();
	println(std::string("</pss:" + t + ">"));
}

void PSI2XML::error(const char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	fputs("Error: ", stdout);
	vfprintf(stdout, fmt, ap);
	fputs("\n", stdout);
	va_end(ap);
}

void PSI2XML::println(const std::string &str) {
	m_content.append(m_ind);
	m_content.append(str);
	m_content.append("\n");
}

void PSI2XML::inc_indent() {
	for (int i=0; i<m_ind_incr; i++) {
		m_ind.append(" ");
	}
}

void PSI2XML::dec_indent() {
	if (m_ind.size() > m_ind_incr) {
		m_ind.resize(m_ind.size()-m_ind_incr);
	} else {
		m_ind.clear();
	}
}

INamedItem *PSI2XML::toNamedItem(IBaseItem *it) {
	switch (it->getType()) {
	case IBaseItem::TypeAction: return static_cast<IAction *>(it);
	case IBaseItem::TypeComponent: return static_cast<IComponent *>(it);
	case IBaseItem::TypeField: return static_cast<IField *>(it);
	case IBaseItem::TypeStruct: return static_cast<IStruct *>(it);
	}

	return 0;
}

}
}
