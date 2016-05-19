/*
 * XML2PSI.cpp
 *
 *  Created on: May 17, 2016
 *      Author: ballance
 */

#include "XML2PSI.h"
#include "PSIUtil.h"
#include <stdio.h>

namespace psi {
namespace apps {

XML2PSI::XML2PSI() {
	// TODO Auto-generated constructor stub

}

void XML2PSI::process(const std::string &content, IModel *model) {
	XML_Parser p = XML_ParserCreate(0);

	m_model = model;
	while (!m_scope_stack.empty()) {
		m_scope_stack.pop();
	}

	XML_SetElementHandler(p, &XML2PSI::start, &XML2PSI::end);
	XML_SetUserData(p, this);

	XML_Parse(p, content.c_str(), content.length(), 0);

	XML_ParserFree(p);
}

XML2PSI::~XML2PSI() {
	// TODO Auto-generated destructor stub
}

void XML2PSI::enter_action(const strmap &attr) {
	IAction *super = 0;

	if (attr.find("super") != attr.end()) {
		// TODO: look up super
	}

	IAction *action = m_model->mkAction(
			attr.find("name")->second, super);
	PSIUtil::toScopeItem(m_scope_stack.top())->add(action);
	m_scope_stack.push(action);
}

void XML2PSI::enter_bit_int_type(bool is_bit, const strmap &attr) {
	IBaseItem *type = 0;

	uint32_t msb=(is_bit)?0:31;
	uint32_t lsb=0;
	strmap::const_iterator msb_i = attr.find("msb");
	strmap::const_iterator lsb_i = attr.find("lsb");

	if (msb_i != attr.end()) {
		msb = strtoul(msb_i->second.c_str(), 0, 0);
	}

	if (lsb_i != attr.end()) {
		lsb = strtoul(lsb_i->second.c_str(), 0, 0);
	}

	type = m_model->mkScalarType(
			(is_bit)?IScalarType::ScalarType_Bit:IScalarType::ScalarType_Int,
					msb, lsb);

	static_cast<IField *>(m_scope_stack.top())->setDataType(type);
	m_scope_stack.push(type);
}

void XML2PSI::enter_component(const strmap &attr) {
	IComponent *comp = m_model->mkComponent(attr.find("name")->second);

	PSIUtil::toScopeItem(m_scope_stack.top())->add(comp);
	m_scope_stack.push(comp);
}

void XML2PSI::enter_field(const strmap &attr) {
	IField::FieldAttr field_attr = IField::FieldAttr_None;
	strmap::const_iterator type = attr.find("type");

	if (type != attr.end()) {
		if (type->second == "rand") {
			field_attr = IField::FieldAttr_Rand;
		} else if (type->second == "input") {
			field_attr = IField::FieldAttr_Input;
		} else if (type->second == "output") {
			field_attr = IField::FieldAttr_Output;
		} else {
			// TODO:
		}
	}

	IField *field = m_model->mkField(attr.at("name"), 0, field_attr);

	PSIUtil::toScopeItem(m_scope_stack.top())->add(field);
	m_scope_stack.push(field);
}

void XML2PSI::enter_literal(const strmap &attr) {
	strmap::const_iterator type_i = attr.find("type");
	strmap::const_iterator value_i = attr.find("value");

	// TODO:
	m_scope_stack.push(0);
}

void XML2PSI::enter_package(const strmap &attr) {
	std::string name;

	if (attr.find("name") != attr.end()) {
		name = attr.find("name")->second;
	}

	if (name == "") {
		m_scope_stack.push(m_model->getGlobalPackage());
	} else {
		m_scope_stack.push(m_model->findPackage(name, true));
	}
}

void XML2PSI::enter_struct_type(const strmap &attr) {
	std::string type = attr.find("type")->second;
	IBaseItem *type_h = 0;

	std::vector<std::string> path = split_path(type);

	IBaseItem *p = m_scope_stack.top(); // parent -- probably a field
	m_scope_stack.pop();
	IScopeItem *s = PSIUtil::toScopeItem(m_scope_stack.top());
	m_scope_stack.push(p); // replace the parent

	type_h = find_type(s, path);

	if (m_scope_stack.top()->getType() == IBaseItem::TypeField) {
		static_cast<IField *>(m_scope_stack.top())->setDataType(type_h);
		m_scope_stack.push(type_h);
	} else {
		// not a field
		fprintf(stdout, "Error: Field not found on the stack\n");
	}
}

void XML2PSI::enter_struct(const std::vector<strpair> &attr) {
	std::string name;
	IStruct *super=0;
	IStruct::StructType type=IStruct::Base;

	for (std::vector<strpair>::const_iterator it=attr.begin();
			it!=attr.end(); it++) {
		strpair p = *it;

		if (p.first == "name") {
			name = p.second;
		} else if (p.first == "super") {
			// TODO: find type
		} else if (p.first == "type") {
			if (p.second == "") {
			} else {
			}
		}
	}

	IStruct *s = m_model->mkStruct(name, type, super);
	IScopeItem *scope = PSIUtil::toScopeItem(m_scope_stack.top());

	if (scope) {
		scope->add(s);
		m_scope_stack.push(s);
	} else {
		fprintf(stdout, "top %p %d is not a scope\n",
				m_scope_stack.top(), m_scope_stack.top()->getType());
	}
}

void XML2PSI::start(const std::string &el, const char **attr) {
	std::vector<strpair> attr_v;
	strmap attr_m;
//	fprintf(stdout, "<%s>\n", el.c_str());
//	fflush(stdout);

	for (int i=0; attr[i]; i+=2) {
		attr_m.insert(strmap_ent(attr[i], attr[i+1]));
		strpair p(attr[i], attr[i+1]);
		attr_v.push_back(p);
	}

	if (el == "model") {
		m_scope_stack.push(m_model);
	} else if (el == "action") {
		enter_action(attr_m);
	} else if (el == "bit" || el == "int") {
		enter_bit_int_type((el == "bit"), attr_m);
	} else if (el == "component") {
		enter_component(attr_m);
	} else if (el == "literal") {
		enter_literal(attr_m);
	} else if (el == "null") {
		m_scope_stack.push(0);
	} else if (el == "package") {
		enter_package(attr_m);
	} else if (el == "field") {
		enter_field(attr_m);
	} else if (el == "struct") {
		if (m_scope_stack.top()->getType() == IBaseItem::TypeField) {
			// Parent is <type>
			enter_struct_type(attr_m);
		} else {
			enter_struct(attr_v);
		}
	} else {
		m_scope_stack.push(0);
	}
}

void XML2PSI::end(const std::string &el) {
	m_scope_stack.pop();
//	fprintf(stdout, "</%s> %s\n", el.c_str(), m_scope_stack.empty()?"true":"false");
//	fflush(stdout);
}

IBaseItem *XML2PSI::find_type(IScopeItem *curr, const std::vector<std::string> &path) {
	IBaseItem *ret = 0;

	if (path.size() == 1) {
		// First look in the containing scope
		if (curr) {
			for (std::vector<IBaseItem *>::const_iterator it=curr->getItems().begin();
					it!=curr->getItems().end(); it++) {
				INamedItem *n_it = PSIUtil::toNamedItem(*it);
				if (n_it && n_it->getName() == path.at(0)) {
					ret = *it;
					break;
				}
			}
		}

		// If we didn't find it there, look in the global scope
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

		ret = scope;
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

}
} /* namespace psi */
