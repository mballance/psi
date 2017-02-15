/*
 * XML2PSI.cpp
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
 *  Created on: May 17, 2016
 *      Author: ballance
 */

#include "XML2PSI.h"

#include <assert.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdint.h>
#include <cstdlib>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

#include "api/IAction.h"
#include "api/IBinaryExpr.h"
#include "api/IComponent.h"
#include "api/IConstraintBlock.h"
#include "api/IConstraintExpr.h"
#include "api/IExec.h"
#include "api/IExecStmt.h"
#include "api/IField.h"
#include "api/IFieldRef.h"
#include "api/IImportFunc.h"
#include "api/ILiteral.h"
#include "api/IModel.h"
#include "api/IPackage.h"
#include "api/IScalarType.h"
#include "api/IStruct.h"
#include "PSIUtil.h"

namespace psi {
namespace apps {

XML2PSI::XML2PSI() {
	// TODO Auto-generated constructor stub

}

void XML2PSI::process(const std::string &content, IModel *model) {
	LIBXML_TEST_VERSION
	m_model = model;

	xmlDocPtr doc;

	// TODO: call validater
	doc = xmlReadMemory(
			content.c_str(),
			content.length(),
			"content.xml",
			0,
			0);

	xmlNode *n = xmlDocGetRootElement(doc);

	for (; n; n=n->next) {
		if (n->type != XML_ELEMENT_NODE) {
			continue;
		}

		std::string name;
		name.append(reinterpret_cast<const char *>(n->name));

		if (name == "model") {
			elaborate_model(n);
		} else {
			fprintf(stdout, "Error: unhandled root element %s\n",
					name.c_str());
		}
	}

	xmlFreeDoc(doc);
}

XML2PSI::~XML2PSI() {
	// TODO Auto-generated destructor stub
}

void XML2PSI::elaborate_model(xmlNode *m) {
	strmap attr;

	m_scope_stack.push(m_model);

	for (xmlNode *n=m->children; n; n=n->next) {

		if (n->type != XML_ELEMENT_NODE) {
			continue;
		}
		std::string name(reinterpret_cast<const char *>(n->name));

		get_attributes(n, attr);
		if (name == "package") {
			elaborate_package(n, attr);
		} else {
			IBaseItem *it = 0;

			if (name == "component") {
				it = elaborate_component(n, attr);
			} else if (name == "struct") {
				it = elaborate_struct(n, attr);
			} else {
				fprintf(stdout, "Error: unhandled model element %s\n",
						name.c_str());
			}

			if (it) {
				if (name == "component") {
					m_model->add(it);
				} else {
					m_model->getGlobalPackage()->add(it);
				}
			} else {
				fprintf(stdout, "Error: Failed to elaborate %s\n", name.c_str());
			}
		}
	}

	m_scope_stack.pop();
}

IAction *XML2PSI::elaborate_action(xmlNode *p, const strmap &attr) {
	strmap attr_m;
	IAction *super = 0;

	fprintf(stdout, "--> elaborate_action %s\n", attr.find("name")->second.c_str());
	if (attr.find("super") != attr.end()) {
		// TODO: look up super
		fprintf(stdout, "Error: action 'super' unsupported\n");
	}

	IAction *a = m_model->mkAction(attr.find("name")->second, super);
	m_scope_stack.push(a);

	for (xmlNode *n=p->children; n; n=n->next) {
		if (n->type != XML_ELEMENT_NODE) {
			continue;
		}

		std::string p_n = reinterpret_cast<const char *>(n->name);
		get_attributes(n, attr_m);
		if (p_n == "activity") {
			IGraphStmt *activity = elaborate_activity(n, attr_m);
			a->setGraph(activity);
		} else {
			a->add(elaborate_action_struct_component_item(n, attr_m));
		}
	}
	m_scope_stack.pop();

	fprintf(stdout, "<-- elaborate_action %s\n", attr.find("name")->second.c_str());

	return a;
}

IGraphStmt *XML2PSI::elaborate_activity(xmlNode *p, const strmap &attr) {
	IGraphBlockStmt *ret = m_model->mkGraphBlockStmt(IGraphStmt::GraphStmt_Block);

	for (xmlNode *n=p->children; n; n=n->next) {
		strmap attr_n;
		if (n->type != XML_ELEMENT_NODE) {
			continue;
		}

		std::string n_n = reinterpret_cast<const char *>(n->name);

		get_attributes(n, attr_n);

		if (n_n == "repeat") {
			ret->add(elaborate_repeat(n, attr_n));
		} else if (n_n == "parallel") {
			ret->add(elaborate_parallel(n, attr_n));
		} else if (n_n == "select") {
			ret->add(elaborate_select(n, attr_n));
		} else if (n_n == "sequential") {
			ret->add(elaborate_sequential(n, attr_n));
		} else if (n_n == "schedule") {
			ret->add(elaborate_schedule(n, attr_n));
		} else if (n_n == "traverse") {
			ret->add(elaborate_traverse(n, attr_n));
		} else {
			fprintf(stdout, "Error: Unknown activity statement: %s\n", n_n.c_str());
		}
	}

	return ret;
}

IGraphBlockStmt *XML2PSI::elaborate_block(IGraphBlockStmt *b, xmlNode *p, const strmap &attr) {

	for (xmlNode *n=p->children; n; n=n->next) {
		strmap attr_n;
		if (n->type != XML_ELEMENT_NODE) {
			continue;
		}

		std::string n_n = reinterpret_cast<const char *>(n->name);

		get_attributes(n, attr_n);

		if (n_n == "repeat") {
			b->add(elaborate_repeat(n, attr_n));
		} else if (n_n == "parallel") {
			b->add(elaborate_parallel(n, attr_n));
		} else if (n_n == "select") {
			b->add(elaborate_select(n, attr_n));
		} else if (n_n == "sequential") {
			b->add(elaborate_sequential(n, attr_n));
		} else if (n_n == "schedule") {
			b->add(elaborate_schedule(n, attr_n));
		} else if (n_n == "traverse") {
			b->add(elaborate_traverse(n, attr_n));
		} else {
			fprintf(stdout, "Error: Unknown activity statement: %s\n", n_n.c_str());
		}
	}

	return b;
}




IGraphBlockStmt *XML2PSI::elaborate_block(xmlNode *p, const strmap &attr) {
	IGraphBlockStmt *ret = m_model->mkGraphBlockStmt(IGraphStmt::GraphStmt_Block);
	return elaborate_block(ret, p, attr);
}

IGraphRepeatStmt *XML2PSI::elaborate_repeat(xmlNode *p, const strmap &attr) {
	std::string type = attr.find("type")->second;
	IExpr *expr = 0;
	IGraphStmt *body = 0;

	xmlNode *e = 0;
	for (xmlNode *n=p->children; n; n=n->next) {
		std::string n_n = reinterpret_cast<const char *>(n->name);
		if (n_n == "expr") {
			strmap attr_c;
			xmlNode *c=n->children;

			// Find the first 'node'
			for (; c; c=c->next) {
				if (c->type == XML_ELEMENT_NODE) {
					break;
				}
			}
			get_attributes(c, attr_c);
			expr = elaborate_expr(c, attr_c);
		} else if (n_n == "body") {
			strmap attr_n;
			get_attributes(n, attr_n);
			body = elaborate_block(n, attr_n);
		}
	}

	IGraphRepeatStmt::RepeatType r_type;

	if (type == "count") {
		r_type = IGraphRepeatStmt::RepeatType_Count;
	} else if (type == "forever") {
		r_type = IGraphRepeatStmt::RepeatType_Forever;
	} else {
		fprintf(stdout, "Error: Unknown repeat type %s\n", type.c_str());
	}

	return m_model->mkGraphRepeatStmt(r_type, expr, body);
}

IGraphBlockStmt *XML2PSI::elaborate_parallel(xmlNode *p, const strmap &attr) {
	return elaborate_block(
			m_model->mkGraphBlockStmt(IGraphBlockStmt::GraphStmt_Parallel),
			p, attr);
}

IGraphBlockStmt *XML2PSI::elaborate_select(xmlNode *p, const strmap &attr) {
	return elaborate_block(
			m_model->mkGraphBlockStmt(IGraphBlockStmt::GraphStmt_Select),
			p, attr);
}

IGraphBlockStmt *XML2PSI::elaborate_sequential(xmlNode *p, const strmap &attr) {
	return elaborate_block(p, attr);
}

IGraphBlockStmt *XML2PSI::elaborate_schedule(xmlNode *p, const strmap &attr) {
	return elaborate_block(
			m_model->mkGraphBlockStmt(IGraphBlockStmt::GraphStmt_Schedule),
			p, attr);
}

IGraphTraverseStmt *XML2PSI::elaborate_traverse(xmlNode *p, const strmap &attr) {
	IFieldRef *action = 0;
	IConstraint *with = 0;

	for (xmlNode *n=p->children; n; n=n->next) {
		std::string n_n = reinterpret_cast<const char *>(n->name);
		if (n_n == "with") {
			strmap attr_n;
			get_attributes(n, attr_n);
			with = elaborate_constraint_set(n, attr_n);
		}
	}

	std::vector<IField *> field_path;
	field_path.push_back(find_field(attr.find("name")->second));
	action = m_model->mkFieldRef(field_path);

	IBaseItem *scope = m_scope_stack.top().scope();

	return m_model->mkGraphTraverseStmt(action, with);
}

IComponent *XML2PSI::elaborate_component(xmlNode *p, const strmap &attr) {
	IComponent *c = m_model->mkComponent(attr.find("name")->second);
	strmap attr_m;

	m_scope_stack.push(c);

	for (xmlNode *n=p->children; n; n=n->next) {
		if (n->type != XML_ELEMENT_NODE) {
			continue;
		}

		std::string name(reinterpret_cast<const char *>(n->name));
		get_attributes(n, attr_m);

		if (name == "action") {
			c->add(elaborate_action(n, attr_m));
		} else if (name == "field") {
			c->add(elaborate_field(n, attr_m));
		} else {
			fprintf(stdout, "Error: unhandled component element %s\n",
					name.c_str());
		}
	}

	m_scope_stack.pop();

	return c;
}

IConstraint *XML2PSI::elaborate_constraint_set(xmlNode *p, const strmap &attr) {
	IConstraint *ret = 0;

	std::string name = reinterpret_cast<const char *>(p->name);

	fprintf(stdout, "elaborate_constraint_set: %s\n", name.c_str());
	fflush(stdout);

	if (name == "stmt") {
		// Find the first child node
		xmlNode *n = p->children;

		while (n && n->type != XML_ELEMENT_NODE) { n=n->next; }
		strmap attr_n;

		get_attributes(n, attr_n);

		ret = m_model->mkConstraintExpr(elaborate_expr(n, attr_n));
	} else if (name == "if") {
		fprintf(stdout, "Error: unsupported constraint %s\n", name.c_str());
	} else if (name == "block") {
		std::vector<IConstraint *> cl;

		for (xmlNode *cn=p->children; cn; cn=cn->next) {
			if (cn->type != XML_ELEMENT_NODE) {
				continue;
			}

			strmap attr_m;
			get_attributes(cn, attr_m);
			cl.push_back(elaborate_constraint_set(cn, attr_m));
		}
		ret = m_model->mkConstraintBlock(name, cl);
	} else if (name == "foreach") {
		fprintf(stdout, "Error: unsupported constraint %s\n", name.c_str());
	} else if (name == "implies") {
		fprintf(stdout, "Error: unsupported constraint %s\n", name.c_str());
	} else {
		fprintf(stdout, "Error: unknown constraint %s\n", name.c_str());
	}

	return ret;
}

IConstraintBlock *XML2PSI::elaborate_constraint_declaration(xmlNode *p, const strmap &attr) {
	std::vector<IConstraint *> cl;
	IConstraintBlock *c = 0;
	std::string c_name;

	fprintf(stdout, "elaborate_constraint_declaration: %s\n", p->name);

	if (attr.find("name") != attr.end()) {
		c_name = attr.find("name")->second;
	}

	for (xmlNode *cn=p->children; cn; cn=cn->next) {
		if (cn->type != XML_ELEMENT_NODE) {
			continue;
		}

		strmap attr_m;
		get_attributes(cn, attr_m);
		cl.push_back(elaborate_constraint_set(cn, attr_m));
	}

	c = m_model->mkConstraintBlock(c_name, cl);

	return c;
}

IExec *XML2PSI::elaborate_exec(xmlNode *p, const strmap &attr) {
	IExec *exec = 0;

	xmlNode *n = p->children;
	while (n && n->type != XML_ELEMENT_NODE) { n=n->next; }

	assert(n);

	std::string name = reinterpret_cast<const char *>(n->name);

	if (name == "block") {
		strmap attr_m;
		get_attributes(n, attr_m);

		std::string kind = attr_m.find("kind")->second;
		IExec::ExecKind kind_e;

		if (kind == "body") {
			kind_e = IExec::Body;
		} else if (kind == "pre_solve") {
			kind_e = IExec::PreSolve;
		} else if (kind == "post_solve") {
			kind_e = IExec::PostSolve;
		}

		std::vector<IExecStmt *> stmts;

		for (xmlNode *cn=n->children; cn; cn=cn->next) {
			if (cn->type != XML_ELEMENT_NODE) {
				continue;
			}

			std::string cn_n = reinterpret_cast<const char *>(cn->name);

			if (cn_n == "assign") {
				xmlNode *cnn = cn->children;
				IExecExprStmt::AssignOp op = toAssignOp(attr_m.find("op")->second);

				while (cnn && cnn->type != XML_ELEMENT_NODE) { cnn=cnn->next; }
				IFieldRef *field = elaborate_variable_ref(cnn);

				while ((cnn=cnn->next) && cnn->type != XML_ELEMENT_NODE) { cnn=cnn->next; }

				IExpr *rhs = elaborate_expr(cnn, attr);

				IExecStmt *stmt = m_model->mkExecExprStmt(field, op, rhs);
				stmts.push_back(stmt);
			} else if (cn_n == "call") {
				IImportFunc *func = 0;
				std::vector<IExpr *> parameters;

				for (xmlNode *n=cn->children; n; n=n->next) {
					if (n->type != XML_ELEMENT_NODE) {
						continue;
					}
					std::string n_n = reinterpret_cast<const char *>(n->name);
					if (n_n == "function") {
						func = find_function(n);
					} else if (n_n == "parameters") {
						for (xmlNode *fp=n->children; fp; fp=fp->next) {
							if (fp->type != XML_ELEMENT_NODE) {
								continue;
							}
							xmlNode *fp_e=fp->children;
							for(; fp_e; fp_e=fp_e->next) {
								if (fp_e->type == XML_ELEMENT_NODE) {
									break;
								}
							}
							strmap attr_fp_e;
							get_attributes(fp_e, attr_fp_e);
							IExpr *e = elaborate_expr(fp_e, attr_fp_e);
							parameters.push_back(e);
						}

					} else {
						fprintf(stdout, "Error: unknown call child %s\n", n_n.c_str());
					}
				}

				IExecCallStmt *call = m_model->mkExecCallStmt(
						0,
						IExecCallStmt::AssignOp_None,
						func,
						parameters);
				stmts.push_back(call);
			} else {
				fprintf(stdout, "Error: unsupported native-exec statement %s\n", cn_n.c_str());
			}
		}

		exec = m_model->mkNativeExec(kind_e, stmts);
	} else if (name == "code_block") {
		fprintf(stdout, "Error: unhandled exec type %s\n", name.c_str());
	} else if (name == "file_block") {
		fprintf(stdout, "Error: unhandled exec type %s\n", name.c_str());
	} else if (name == "inline") {
		fprintf(stdout, "Error: unhandled exec type %s\n", name.c_str());
	} else {
		fprintf(stdout, "Error: unhandled exec type %s\n", name.c_str());
	}


	return exec;
}

IExpr *XML2PSI::elaborate_expr(xmlNode *p, const strmap &attr) {
	std::string name;
	IExpr *ret = 0;

	// Skip leading non-element nodes

	name = reinterpret_cast<const char *>(p->name);

	fprintf(stdout, "elaborate_expr: %s\n", name.c_str());
	fflush(stdout);

	if (name == "binexp") {
		xmlNode *lhs = 0;
		xmlNode *rhs = 0;

		for (xmlNode *cn=p->children; cn; cn=cn->next) {
			if (cn->type != XML_ELEMENT_NODE) {
				continue;
			}
			name = reinterpret_cast<const char *>(cn->name);


			if (name == "lhs") {
				lhs = cn;
			} else if (name == "rhs") {
				rhs = cn;
			} else {
				fprintf(stdout, "Error: unknown binexp child %s\n", name.c_str());
			}
		}

		assert(lhs);
		assert(rhs);

		// Find the first element child of lhs and rhs
		lhs = lhs->children;
		while (lhs && lhs->type != XML_ELEMENT_NODE) { lhs = lhs->next; }

		rhs = rhs->children;
		while (rhs && rhs->type != XML_ELEMENT_NODE) { rhs = rhs->next; }

		assert(lhs);
		assert(rhs);

		strmap attr_lhs, attr_rhs;
		get_attributes(lhs, attr_lhs);
		get_attributes(rhs, attr_rhs);

		IBinaryExpr::BinOpType op = toBinOp(attr.find("op")->second);

		ret = m_model->mkBinExpr(
				elaborate_expr(lhs, attr_lhs),
				toBinOp(attr.find("op")->second),
				elaborate_expr(rhs, attr_rhs));
	} else if (name == "unexp") {
		fprintf(stdout, "Error: unhandled expr element %s\n", name.c_str());
	} else if (name == "inside") {
		fprintf(stdout, "Error: unhandled expr element %s\n", name.c_str());
	} else if (name == "number") {
		const char *v = reinterpret_cast<const char *>(xmlNodeListGetString(p->doc, p->children, 1));
		uint64_t v_i = strtoul(v, 0, 0);
		ret = m_model->mkIntLiteral(v_i);
	} else if (name == "paren") {
		fprintf(stdout, "Error: unhandled expr element %s\n", name.c_str());
	} else if (name == "ref") {
		ret = elaborate_field_ref(p);

	} else if (name == "call") {
		fprintf(stdout, "Error: unhandled expr element %s\n", name.c_str());
	} else {
		fprintf(stdout, "Error: unknown expr element %s\n", name.c_str());
	}

	return ret;
}

IBaseItem *XML2PSI::elaborate_type(xmlNode *p, const strmap &attr) {
	IBaseItem *type = 0;
	xmlNode *n = p->children;
	std::string name;

	while (n && n->type != XML_ELEMENT_NODE) { n = n->next; }

	name = reinterpret_cast<const char *>(n->name);

	if (name == "int" || name == "bit") {
		strmap attr_m;

		// Must look inside the containing element

		IExpr *msb = 0, *lsb=0;

		for (n=n->children; n; n=n->next) {
			if (n->type != XML_ELEMENT_NODE) {
				continue;
			}

			std::string c_name = reinterpret_cast<const char *>(n->name);

			if (c_name == "msb") {
				xmlNode *cn = n->children;
				while (cn && cn->type != XML_ELEMENT_NODE) { cn=cn->next; }
				assert(cn);
				get_attributes(cn, attr_m);
				msb = elaborate_expr(cn, attr_m);
			} else if (c_name == "lsb") {
				xmlNode *cn = n->children;
				while (cn && cn->type != XML_ELEMENT_NODE) { cn=cn->next; }
				assert(cn);
				get_attributes(cn, attr_m);
				lsb = elaborate_expr(cn, attr_m);
			}
		}

		if (name == "int") {
			type = m_model->mkScalarType(IScalarType::ScalarType_Int, msb, lsb);
		} else {
			type = m_model->mkScalarType(IScalarType::ScalarType_Bit, msb, lsb);
		}
	} else if (name == "bool") {
		type = m_model->mkScalarType(IScalarType::ScalarType_Bool, 0, 0);
	} else if (name == "chandle") {
		type = m_model->mkScalarType(IScalarType::ScalarType_Chandle, 0, 0);
	} else if (name == "string") {
		type = m_model->mkScalarType(IScalarType::ScalarType_String, 0, 0);
	} else if (name == "user") {
		type = find_type(n);
	} else {
		// user-defined type
		fprintf(stdout, "Error: Unhandled type \"%s\"\n", name.c_str());
	}

	return type;
}


IField *XML2PSI::elaborate_field(xmlNode *p, const strmap &attr) {
	IField *field = 0;
	IField::FieldAttr field_attr = IField::FieldAttr_None;
	strmap attr_m;
	strmap::const_iterator q = attr.find("qualifier");

	if (q != attr.end()) {
		fprintf(stdout, "Qualifier: for field %s %s\n",
				attr.at("name").c_str(), q->second.c_str());
		if (q->second == "rand") {
			field_attr = IField::FieldAttr_Rand;
		} else if (q->second == "input") {
			field_attr = IField::FieldAttr_Input;
		} else if (q->second == "output") {
			field_attr = IField::FieldAttr_Output;
		} else if (q->second == "lock") {
			field_attr = IField::FieldAttr_Lock;
		} else if (q->second == "share") {
			field_attr = IField::FieldAttr_Share;
		} else if (q->second == "pool") {
			field_attr = IField::FieldAttr_Pool;
		} else {
			// TODO: Error
		}
	}

	IBaseItem *field_t = 0;
	xmlNode *n = p->children;
	std::string name;

	while (n && n->type != XML_ELEMENT_NODE) { n = n->next; }
	assert(n);

	// Expect this to be 'type'
	name = reinterpret_cast<const char *>(n->name);

	if (name == "type") {
		get_attributes(n, attr_m);
		field_t = elaborate_type(n, attr_m);
	} else {
		fprintf(stdout, "Error: unhandled field element %s\n", name.c_str());
	}

	// May have an array dimension component
	IExpr *array_dim = 0;
	if (n) {
		n = n->next;
		while (n && n->type != XML_ELEMENT_NODE) { n = n->next; }

		if (n) {
			name = reinterpret_cast<const char *>(n->name);

			if (name == "dim") {
				get_attributes(n, attr_m);
				array_dim = elaborate_expr(n, attr_m);
			} else {
				fprintf(stdout, "Error: unhandled field element %s\n", name.c_str());
			}
		}
	}

	fprintf(stdout, "Field: %s attr=%d\n", attr.at("name").c_str(), field_attr);

	field = m_model->mkField(
			attr.at("name"),
			field_t,
			field_attr,
			array_dim);

	return field;
}

IFieldRef *XML2PSI::elaborate_field_ref(xmlNode *p) {
	IBaseItem *ctxt = m_scope_stack.top().scope();
	IField *f = 0;
	std::vector<IField *> path;

	for (xmlNode *cn = p->children; cn; cn=cn->next) {
		if (cn->type != XML_ELEMENT_NODE) {
			continue;
		}

		std::string c_name = reinterpret_cast<const char *>(cn->name);

		if (c_name == "path") {
			std::string v = reinterpret_cast<const char *>(xmlNodeListGetString(cn->doc, cn->children, 1));

			IScopeItem *scope;

			if (!(scope = dynamic_cast<IScopeItem *>(ctxt))) {
				fprintf(stdout, "Error: context isnt't a scope\n");
			}

			IField *f_i = 0;
			// Search for this element in the current scope
			for (std::vector<IBaseItem *>::const_iterator it=scope->getItems().begin();
					it!=scope->getItems().end(); it++) {
				if ((f_i = dynamic_cast<IField *>(*it)) && f_i->getName() == v) {
					break;
				} else {
					f_i = 0;
				}
			}

			if (!f_i) {
				fprintf(stdout, "Error: Failed to find element %s\n", v.c_str());
				f = 0;
				break;
			} else {
				path.push_back(f_i);
				f = f_i;
				ctxt = f_i->getDataType();
			}
		} else {
			fprintf(stdout, "Error: unknown ref sub-element %s\n", c_name.c_str());
		}
	}

	if (!f) {
		fprintf(stdout, "Error: Failed to find referenced field\n");
	}

	return m_model->mkFieldRef(path);
}

IImportFunc *XML2PSI::elaborate_import_function(xmlNode *p, const strmap &attr) {
	IBaseItem *ret_type = 0;
	std::string name = attr.find("name")->second;
	std::vector<IField *> parameters;

	xmlNode *n = p->children;

	while (n && n->type != XML_ELEMENT_NODE) { n=n->next; }

	assert(n);

	std::string nn = reinterpret_cast<const char *>(n->name);
	if (nn == "return") {
		strmap attr_m;
		get_attributes(n, attr_m);
		ret_type = elaborate_type(n, attr_m);
		n=n->next;
	}

	while (n && n->type != XML_ELEMENT_NODE) { n=n->next; }
	assert(n);

	nn = reinterpret_cast<const char *>(n->name);

	if (nn == "parameters") {
		for (xmlNode *cn = n->children; cn; cn=cn->next) {
			if (cn->type != XML_ELEMENT_NODE) {
				continue;
			}

			nn = reinterpret_cast<const char *>(cn->name);
			if (nn == "parameter") {
				strmap attr_m;
				get_attributes(cn, attr_m);

				parameters.push_back(elaborate_parameter(cn, attr_m));
			} else {
				fprintf(stdout, "Error: unknown parameter-list element %s\n", nn.c_str());
			}
		}
	} else {
		fprintf(stdout, "Error: unknown import_function sub-element %s\n", nn.c_str());
	}

	return m_model->mkImportFunc(name, ret_type, parameters);
}

void XML2PSI::elaborate_import_stmt(xmlNode *p, const strmap &attr) {
	IScopeItem *scope = m_model;
	IBaseItem *imp = 0;

	for (xmlNode *c=p->children; c; c=c->next) {
		if (c->type != XML_ELEMENT_NODE) {
			continue;
		}

		std::string name = reinterpret_cast<const char *>(c->name);

		if (imp) {
			scope = dynamic_cast<IScopeItem *>(imp);
		}

		if (name == "path") {
			const char *v = reinterpret_cast<const char *>(xmlNodeListGetString(c->doc, c->children, 1));

			// Search in 'scope'
			INamedItem *ni = 0;
			imp=0;
			for (std::vector<IBaseItem *>::const_iterator it=scope->getItems().begin();
					it!=scope->getItems().end(); it++) {

				if ((ni=dynamic_cast<INamedItem *>(*it)) &&
						ni->getName() == v) {
					imp = *it;
					break;
				} else {
					imp = 0;
				}
			}

			if (!imp) {
				fprintf(stdout, "Error: failed to find path element %s\n", v);
				break;
			}
		} else {
			fprintf(stdout, "Error: Unknown import_stmt element %s\n", name.c_str());
		}
	}

	if (imp) {
		m_scope_stack.top().add_import(imp);
	}
}

IField *XML2PSI::elaborate_parameter(xmlNode *p, const strmap &attr) {
	IField *f = 0;
	xmlNode *n = p->children;

	while (n && n->type != XML_ELEMENT_NODE) { n=n->next; }
	assert(n);

	// We're assuming this is a type
	strmap attr_m;
	get_attributes(n, attr_m);
	IBaseItem *field_type = elaborate_type(n, attr_m);

	// TODO:
	IExpr *array_dim = 0;
	IField::FieldAttr field_attr = IField::FieldAttr_Input;

	if (attr.find("dir") != attr.end()) {
		if (attr.find("dir")->second == "input") {
			field_attr = IField::FieldAttr_Input;
		} else if (attr.find("dir")->second == "output") {
			field_attr = IField::FieldAttr_Output;
		} else if (attr.find("dir")->second == "inout") {
			field_attr = IField::FieldAttr_Inout;
		}
	}

	f = m_model->mkField(attr.find("name")->second,
			field_type, field_attr, array_dim);

	return f;
}

void XML2PSI::elaborate_package(xmlNode *p, const strmap &attr) {
	std::string name;
	strmap attr_m;
	IPackage *pkg;

	if (attr.find("name") != attr.end()) {
		name = attr.find("name")->second;
	}

	if (name == "") {
		pkg = m_model->getGlobalPackage();
	} else {
		pkg = m_model->findPackage(name, true);
	}


	m_scope_stack.push(Context(pkg));

	for (xmlNode *n=p->children; n; n=n->next) {
		if (n->type != XML_ELEMENT_NODE) {
			continue;
		}
		std::string name(reinterpret_cast<const char *>(n->name));
		get_attributes(n, attr_m);

		if (name == "action") {
			fprintf(stdout, "Error: unhandled package element %s\n", name.c_str());
		} else if (name == "struct") {
			pkg->add(elaborate_struct(n, attr_m));
		} else if (name == "import_function") {
			pkg->add(elaborate_import_function(n, attr_m));
		} else if (name == "import_stmt") {
			elaborate_import_stmt(n, attr_m);
		} else {
			fprintf(stdout, "Error: unhandled package element %s\n",
					name.c_str());
		}
	}

	m_scope_stack.pop();
}

IStruct *XML2PSI::elaborate_struct(xmlNode *p, const strmap &attr) {
	strmap::const_iterator name_i = attr.find("name");
	strmap::const_iterator qual_i = attr.find("qualifier");

	IStruct::StructType type = IStruct::Base;

	if (qual_i != attr.end()) {
		// Qualfied
		if (qual_i->second == "memory") {
			type = IStruct::Memory;
		} else if (qual_i->second == "stream") {
			type = IStruct::Stream;
		} else if (qual_i->second == "state") {
			type = IStruct::State;
		} else if (qual_i->second == "resource") {
			type = IStruct::Resource;
		}
	}

	xmlNode *c = p->children;
	IStruct *super_type = 0;

	if (c && std::string("super") == reinterpret_cast<const char *>(c->name)) {
		// TODO: locate supertype
		c = c->next;
	}

	IStruct *ret = m_model->mkStruct(
			name_i->second, type, super_type);
	m_scope_stack.push(ret);

	// Process body items
	for (; c; c=c->next) {
		strmap attr;
		if (c->type != XML_ELEMENT_NODE) {
			continue;
		}

		get_attributes(c, attr);

		ret->add(elaborate_action_struct_component_item(c, attr));
	}

	m_scope_stack.pop();

	return ret;
}

IBaseItem *XML2PSI::elaborate_action_struct_component_item(xmlNode *p, const strmap &attr) {
	IBaseItem *ret = 0;
	std::string p_n = reinterpret_cast<const char *>(p->name);

	if (p_n == "field") {
		ret = elaborate_field(p, attr);
	} else if (p_n == "constraint") {
		ret = elaborate_constraint_declaration(p, attr);
	} else if (p_n == "exec") {
		ret = elaborate_exec(p, attr);
	} else {
		fprintf(stdout, "Error: unhandled action_struct_component_item %s\n", p_n.c_str());
	}

	return ret;
}

IFieldRef *XML2PSI::elaborate_variable_ref(xmlNode *p) {
	return 0;
}

IBaseItem *XML2PSI::find_type(IScopeItem *curr, const std::vector<std::string> &path) {
	IBaseItem *ret = 0;

	if (path.size() == 1) {
		// First look in the containing scope
		fprintf(stdout, "find_type curr=%d\n",
				(curr)?dynamic_cast<IBaseItem *>(curr)->getType():-1);
		if (curr) {
			for (std::vector<IBaseItem *>::const_iterator it=curr->getItems().begin();
					it!=curr->getItems().end(); it++) {
				fprintf(stdout, "it=%d\n", (*it)->getType());
				INamedItem *n_it = PSIUtil::toNamedItem(*it);
				if (n_it && n_it->getName() == path.at(0)) {
					ret = *it;
					break;
				}
			}
		}

		// pss_if we didn't find it there, look in the global scope
		if (!ret) {
			const std::vector<IBaseItem *> &items =
					m_model->getGlobalPackage()->getItems();
			for (std::vector<IBaseItem *>::const_iterator it=items.begin();
					it!=items.end(); it++) {
				INamedItem *n_it = PSIUtil::toNamedItem(*it);

				if (n_it && n_it->getName() == path.at(0)) {
					ret = *it;
					break;
				}
			}
		}
	} else {
		// absolute path (?)
		fprintf(stdout, "Error: TODO - qualified scope search\n");
		fflush(stdout);

		IScopeItem *scope = m_model;

		for (std::vector<std::string>::const_iterator p_it=path.begin();
				p_it!=path.end(); p_it++) {
			IBaseItem *n = 0;
			for (std::vector<IBaseItem *>::const_iterator it=scope->getItems().begin();
					it!=scope->getItems().end(); it++) {
				INamedItem *n_it = PSIUtil::toNamedItem(*it);
				if (n_it && n_it->getName() == *p_it) {
					n = *it;
					break;
				}
			}

			if (n) {
				scope = PSIUtil::toScopeItem(n);
				if (!scope) {
					break;
				}
			} else {
				scope = 0;
				break;
			}
		}

		ret = dynamic_cast<IBaseItem *>(scope);
	}

	return ret;
}

std::vector<std::string> XML2PSI::split_path(const std::string &path) {
	std::vector<std::string> ret;

	uint32_t i;
	int32_t start=0;

	for (i=0; i<path.size(); i++) {
		if (path.at(i) == ':') {
			ret.push_back(path.substr(start, i-start));
			i++; // skip next colon
			start = i;
		}
	}

	ret.push_back(path.substr(start, i-start));

	return ret;
}

void XML2PSI::get_attributes(xmlNode *n, strmap &attr_m) {
	attr_m.clear();

	for (xmlAttrPtr attr=n->properties; attr; attr=attr->next) {
		std::string name = reinterpret_cast<const char *>(attr->name);
		std::string value = reinterpret_cast<const char *>(xmlGetProp(n, attr->name));
		attr_m.insert(strmap_ent(name, value));
	}
}

IExecExprStmt::AssignOp XML2PSI::toAssignOp(const std::string &op) {
	if (op == "Eq") {
		return IExecExprStmt::AssignOp_Eq;
	} else if (op == "PlusEq") {
		return IExecExprStmt::AssignOp_PlusEq;
	} else if (op == "MinusEq") {
		return IExecExprStmt::AssignOp_MinusEq;
	} else if (op == "LShiftEq") {
		return IExecExprStmt::AssignOp_LShiftEq;
	} else if (op == "RShiftEq") {
		return IExecExprStmt::AssignOp_RShiftEq;
	} else if (op == "OrEq") {
		return IExecExprStmt::AssignOp_OrEq;
	} else if (op == "AndEq") {
		return IExecExprStmt::AssignOp_AndEq;
	} else {
		fprintf(stdout, "Error: Unknown assign op %s\n", op.c_str());
		return IExecExprStmt::AssignOp_Eq;
	}
}

IBinaryExpr::BinOpType XML2PSI::toBinOp(const std::string &op) {
	if (op == "Eq") {
		return IBinaryExpr::BinOp_Eq;
	} else if (op == "EqEq") {
		return IBinaryExpr::BinOp_EqEq;
	} else if (op == "NotEq") {
		return IBinaryExpr::BinOp_NotEq;
	} else if (op == "GE") {
		return IBinaryExpr::BinOp_GE;
	} else if (op == "GT") {
		return IBinaryExpr::BinOp_GT;
	} else if (op == "LE") {
		return IBinaryExpr::BinOp_LE;
	} else if (op == "LT") {
		return IBinaryExpr::BinOp_LT;
	} else if (op == "And") {
		return IBinaryExpr::BinOp_And;
	} else if (op == "AndAnd") {
		return IBinaryExpr::BinOp_AndAnd;
	} else if (op == "Or") {
		return IBinaryExpr::BinOp_Or;
	} else if (op == "OrOr") {
		return IBinaryExpr::BinOp_OrOr;
	} else if (op == "Minus") {
		return IBinaryExpr::BinOp_Minus;
	} else if (op == "Plus") {
		return IBinaryExpr::BinOp_Plus;
	} else if (op == "Mul") {
		return IBinaryExpr::BinOp_Multiply;
	} else if (op == "Mod") {
		return IBinaryExpr::BinOp_Mod;
	} else if (op == "ArrRef") {
		return IBinaryExpr::BinOp_ArrayRef;
	} else {
		fprintf(stdout, "Error: Unknown binary op %s\n", op.c_str());
		return IBinaryExpr::BinOp_Eq;
	}
}

IBaseItem *XML2PSI::find_type(xmlNode *p) {
	IScopeItem *scope = 0;
//	dynamic_cast<IScopeItem *>(m_scope_stack.top());
	std::vector<std::string> pl;

	for (xmlNode *c=p->children; c; c=c->next) {
		if (c->type != XML_ELEMENT_NODE) {
			continue;
		}

		std::string path = reinterpret_cast<const char *>(
				xmlNodeListGetString(c->doc, c->children, 1));
		pl.push_back(path);
	}

	IBaseItem *top = m_scope_stack.top().scope();
	m_scope_stack.pop();
	IBaseItem *top_p = (!m_scope_stack.empty())?m_scope_stack.top().scope():0;
	IBaseItem *ret;

	if (!(ret=find_type(dynamic_cast<IScopeItem *>(top), pl))) {
		if (top_p) {
			ret = find_type(dynamic_cast<IScopeItem *>(top_p), pl);
		}
	}

	if (top_p) {
		m_scope_stack.push(top_p);
	}
	m_scope_stack.push(top);

	if (!ret) {
		fprintf(stdout, "Error: Failed to find type ");
		for (uint32_t i=0; i<pl.size(); i++) {
			fprintf(stdout, "%s", pl.at(i).c_str());
			if (i+1<pl.size()) {
				fprintf(stdout, "::");
			}
		}
		fprintf(stdout, "\n");
	}

	return ret;
}

IField *XML2PSI::find_field(const std::string &name) {
	IScopeItem *scope = dynamic_cast<IScopeItem *>(m_scope_stack.top().scope());

	return scope->getField(name);
}

IImportFunc *XML2PSI::find_function(xmlNode *p) {
	// TODO: need to look through imports (I assume)
	IImportFunc *func = 0;

	// Start at root
	IScopeItem *s = 0;
	for (xmlNode *c=p->children; c; c=c->next) {
		if (c->type != XML_ELEMENT_NODE) {
			continue;
		}
		std::string c_n = reinterpret_cast<const char *>(c->name);
		fprintf(stdout, "c_n=%s\n", c_n.c_str());
		if (c_n == "path") {
			std::string path = reinterpret_cast<const char *>(
					xmlNodeListGetString(c->doc, c->children, 1));

			fprintf(stdout, "path=%s\n", path.c_str());

			if (!s) {
				// First element. Could be a global function, or this could be a component/package name

				for (std::vector<IBaseItem *>::const_iterator
						it=m_model->getGlobalPackage()->getItems().begin();
						it!=m_model->getGlobalPackage()->getItems().end(); it++) {
					INamedItem *ni = dynamic_cast<INamedItem *>(*it);
					if (ni && ni->getName() == path) {
						func = dynamic_cast<IImportFunc *>(*it);
						s = dynamic_cast<IScopeItem *>(*it);

						if (func || s) {
							break;
						}
					}
				}

				if (!func && !s) {
					// Perform the same search on top-level items
					for (std::vector<IBaseItem *>::const_iterator
							it=m_model->getItems().begin();
							it!=m_model->getItems().end(); it++) {
						INamedItem *ni = dynamic_cast<INamedItem *>(*it);
						if (ni && ni->getName() == path) {
							s = dynamic_cast<IScopeItem *>(*it);
							break;
						}
					}
				}
			} else {
				// Search inside
				for (std::vector<IBaseItem *>::const_iterator
						it=s->getItems().begin(); it!=s->getItems().end(); it++) {
					INamedItem *ni = dynamic_cast<INamedItem *>(*it);

					if (ni && ni->getName() == path) {
						func = dynamic_cast<IImportFunc *>(*it);
						s = dynamic_cast<IScopeItem *>(*it);
						break;
					}
				}
			}
		} else {
			fprintf(stdout, "Error: unknown function path-element %s\n", c_n.c_str());
		}
	}

	fprintf(stdout, "func=%p\n", func);

	return func;
}


} /* namespace apps */
} /* namespace psi */
