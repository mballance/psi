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

namespace psi {
namespace apps {

PSI2XML::PSI2XML() : m_ind_incr(4) {
	// TODO Auto-generated constructor stub

}

PSI2XML::~PSI2XML() {
	// TODO Auto-generated destructor stub
}

const std::string &PSI2XML::traverse(IModel *model) {
	m_content.clear();

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
		}
	}


	return m_content;
}

void PSI2XML::process_pkg(IPackage *pkg) {
	if (pkg->getName() == "") {
		println("<package>");
	} else {
		println("<package name=\"" + pkg->getName() + "\">");
	}

	inc_indent();

	std::vector<IBaseItem *>::const_iterator it=pkg->getItems().begin();

	for (; it!=pkg->getItems().end(); it++) {
		IBaseItem *i = *it;

		switch (i->getType()) {
			case IBaseItem::TypeAction:
				break;

			case IBaseItem::TypeStruct:
				process_struct(static_cast<IStruct *>(i));
				break;
		}
	}

	dec_indent();

	println("</package>");
}

void PSI2XML::process_action(IAction *a) {
	IAction *super_a = 0; // TODO: super-type

	std::string tag = "<action name=\"" + a->getName() + "\"";

	if (super_a) {
		tag += " super=\"" + super_a->getName() + "\"";
	}

	tag += ">";
	println(tag);

	inc_indent();
	process_body(a->getItems());
	dec_indent();

	println("</action>");
}

void PSI2XML::process_struct(IStruct *str) {
	IStruct *super_s = 0; // TODO: super-type
	std::string tag = "<struct name=\"" + str->getName() + "\"";

	// TODO: handle super-type
	tag += ">";
	println(tag);

	inc_indent();
	process_body(str->getItems());
	dec_indent();

	println("</struct>");
}

void PSI2XML::process_body(const std::vector<IBaseItem *> &items) {
	std::vector<IBaseItem *>::const_iterator it = items.begin();

	for (; it!=items.end(); it++) {
		IBaseItem *i = *it;

		switch (i->getType()) {
		case IBaseItem::TypeConstraint:
			process_constraint_block(static_cast<IConstraintBlock *>(i));
			break;

		case IBaseItem::TypeField:
			process_field(static_cast<IField *>(i));
			break;

		default:
			fprintf(stdout, "Error: Unknown body item %d\n", i->getType());
		}
	}
}

void PSI2XML::process_component(IComponent *c) {

	println(std::string("<component name=\"") + c->getName() + "\">");
	inc_indent();

	process_comp_pkg_body(c->getItems());

	dec_indent();
	println("</component>");
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

void PSI2XML::process_constraint(IConstraint *c) {
	switch (c->getConstraintType()) {
	case IConstraint::ConstraintType_Block:
		fprintf(stdout, "  block\n");
		break;

	case IConstraint::ConstraintType_Expr:
		process_expr(static_cast<IConstraintExpr *>(c)->getExpr());
		break;

	case IConstraint::ConstraintType_If: {
		IConstraintIf *c_if = static_cast<IConstraintIf *>(c);

		println("<if>");
		inc_indent();
		println("<cond>");
		inc_indent();
		process_expr(c_if->getCond());
		dec_indent();
		println("</cond>");

		println("<isTrue>");
		inc_indent();
		process_constraint(c_if->getTrue());
		dec_indent();
		println("</isTrue>");

		if (c_if->getFalse()) {
			println("<isFalse>");
			inc_indent();
			process_constraint(c_if->getFalse());
			dec_indent();
			println("</isFalse>");
		}

		dec_indent();
		println("</if>");

		fprintf(stdout, "  if\n");
		} break;
	}
}

void PSI2XML::process_constraint_block(IConstraintBlock *block) {
	std::vector<IConstraint *>::const_iterator it = block->getConstraints().begin();

	if (block->getName() == "") {
		println("<constraint>");
	} else {
		println("<constraint name=\"" + block->getName() + "\">");
	}

	inc_indent();

	for (; it!=block->getConstraints().end(); it++) {
		IConstraint *c = *it;
		process_constraint(c);
	}

	dec_indent();

	println("</constraint>");
}

void PSI2XML::process_expr(IExpr *e) {
	if (!e) {
		fprintf(stdout, "Error: null expression\n");
		return;
	}
	switch (e->getType()) {
		case IExpr::ExprType_BinOp: {
			IBinaryExpr *be = static_cast<IBinaryExpr *>(e);
			std::string op = "<unknown>";
			switch (be->getBinOpType()) {
			case IBinaryExpr::BinOp_EqEq: op = "=="; break;
			case IBinaryExpr::BinOp_NotEq: op = "!="; break;
			case IBinaryExpr::BinOp_GE: op = ">="; break;
			case IBinaryExpr::BinOp_GT: op = ">"; break;
			case IBinaryExpr::BinOp_LE: op = "<="; break;
			case IBinaryExpr::BinOp_LT: op = "<"; break;
			case IBinaryExpr::BinOp_And: op = "&"; break;
			case IBinaryExpr::BinOp_AndAnd: op = "&&"; break;
			case IBinaryExpr::BinOp_Or: op = "|"; break;
			case IBinaryExpr::BinOp_OrOr: op = "||"; break;
			case IBinaryExpr::BinOp_Minus: op = "-"; break;
			case IBinaryExpr::BinOp_Plus: op = "+"; break;
			case IBinaryExpr::BinOp_Multiply: op = "*"; break;
			case IBinaryExpr::BinOp_Divide: op = "/"; break;
			case IBinaryExpr::BinOp_Mod: op = "%"; break;
			case IBinaryExpr::BinOp_ArrayRef: op = "[]"; break;
			}
			println("<binexp op=\"" + op + "\">");
			inc_indent();
			process_expr(be->getLHS());
			process_expr(be->getRHS());
			dec_indent();
			println("</binexp>");
			} break;

		case IExpr::ExprType_Literal: {
			ILiteral *l = static_cast<ILiteral *>(e);
			std::string tag;
			char val[64];

			switch (l->getLiteralType()) {
			case ILiteral::LiteralBit: {
				sprintf(val, "0x%llx", (long long)l->getBit());
				tag = "<bit value=\"";
				tag += val;
				tag += "\"/>";
			} break;
			case ILiteral::LiteralInt: {
				sprintf(val, "0x%llx", (long long)l->getInt());
				tag = "<int value=\"";
				tag += val;
				tag += "\"/>";
			} break;
			case ILiteral::LiteralBool: {
				tag = "<bool value=\"";
				if (l->getBool()) {
					tag += "true";
				} else {
					tag += "false";
				}
				tag += "\"/>";
			} break;
			default:
				tag = "<unknown/>";
			}

			println(tag);

			} break;

		case IExpr::ExprType_FieldRef:
			std::string tag = "<field name=\"";
			tag += static_cast<IFieldRef *>(e)->getField()->getName() + "\"/>";
			println(tag);
			break;
	}
}

void PSI2XML::process_field(IField *f) {
	char msb_s[64], lsb_s[64];
	std::string tag = "<field name=\"" + f->getName() + "\"";

	switch (f->getAttr()) {
	case IField::FieldAttr_Rand:
		tag += " isRand=\"true\"";
		break;
	case IField::FieldAttr_Input:
		tag += " isInput=\"true\"";
		break;
	case IField::FieldAttr_Output:
		tag += " isOutput=\"true\"";
		break;
	}

	tag += ">";
	println(tag);

	inc_indent();
	println("<type>");
	inc_indent();

	IBaseItem *dt_i = f->getDataType();

	if (dt_i->getType() == IBaseItem::TypeScalar) {
		IScalarType *st = static_cast<IScalarType *>(dt_i);
		std::string tname = "unknown";
		sprintf(msb_s, "%d", st->getMSB());
		sprintf(lsb_s, "%d", st->getLSB());
		bool has_bitwidth = false;

		if (st->getScalarType() == IScalarType::ScalarType_Bit) {
			tname = "bit";
			has_bitwidth = true;
		} else if (st->getScalarType() == IScalarType::ScalarType_Int) {
			tname = "int";
			has_bitwidth = true;
		}

		if (has_bitwidth) {
			println(std::string("<") + tname + " msb=\"" +
					msb_s + "\" lsb=\"" + lsb_s + "\"/>");
		} else {
			println(std::string("<") + tname + "/>");
		}
	} else if (dt_i->getType() == IBaseItem::TypeAction) {
	} else if (dt_i->getType() == IBaseItem::TypeStruct) {

	} else {
		println("<unknown/>");
	}
	dec_indent();

	println("</type>");
	dec_indent();

	println("</field>");
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


}
}
