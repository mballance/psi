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

	fprintf(stdout, "doc=%p\n", doc);

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

//	XML_Parser p = ::XML_ParserCreate(0);
//
//	while (!m_scope_stack.empty()) {
//		pop();
//	}
//
//	::XML_SetElementHandler(p, &XML2PSI::start, &XML2PSI::end);
//	::XML_SetUserData(p, this);
//
//	::XML_Parse(p, content.c_str(), content.length(), 0);
//
//	::XML_ParserFree(p);
}

XML2PSI::~XML2PSI() {
	// TODO Auto-generated destructor stub
}

void XML2PSI::elaborate_model(xmlNode *m) {
	strmap attr;

	for (xmlNode *n=m->children; n; n=n->next) {
		if (n->type != XML_ELEMENT_NODE) {
			continue;
		}
		std::string name(reinterpret_cast<const char *>(n->name));

		get_attributes(n, attr);
		if (name == "package") {
			elaborate_package(n, attr);
		} else if (name == "component") {
			m_model->add(elaborate_component(n, attr));
		} else {
			fprintf(stdout, "Error: unhandled model element %s\n",
					name.c_str());
		}
	}
}

IAction *XML2PSI::elaborate_action(xmlNode *p, const strmap &attr) {
	strmap attr_m;
	IAction *super = 0;

	if (attr.find("super") != attr.end()) {
		// TODO: look up super
	}

	IAction *a = m_model->mkAction(
			attr.find("name")->second, super);

	for (xmlNode *n=p->children; n; n=n->next) {
		if (n->type != XML_ELEMENT_NODE) {
			continue;
		}

		std::string name(reinterpret_cast<const char *>(n->name));
		get_attributes(n, attr_m);

		if (name == "field") {
			a->add(elaborate_field(n, attr_m));
		} else {
			fprintf(stdout, "Error: unhandled action element %s\n", name.c_str());
		}
	}

	return a;
}

IComponent *XML2PSI::elaborate_component(xmlNode *p, const strmap &attr) {
	IComponent *c = m_model->mkComponent(attr.find("name")->second);
	strmap attr_m;

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

	return c;
}

IField *XML2PSI::elaborate_field(xmlNode *p, const strmap &attr) {
	IField *field = 0;
	IField::FieldAttr field_attr = IField::FieldAttr_None;
	strmap attr_m;
	strmap::const_iterator type = attr.find("type");

	if (type != attr.end()) {
		if (type->second == "rand") {
			field_attr = IField::FieldAttr_Rand;
		} else if (type->second == "input") {
			field_attr = IField::FieldAttr_Input;
		} else if (type->second == "output") {
			field_attr = IField::FieldAttr_Output;
		} else if (type->second == "lock") {
			field_attr = IField::FieldAttr_Lock;
		} else if (type->second == "share") {
			field_attr = IField::FieldAttr_Share;
		} else if (type->second == "pool") {
			field_attr = IField::FieldAttr_Pool;
		} else {
			// TODO: Error
		}
	}

	IBaseItem *field_t = 0;
	for (xmlNode *n=p->children; n; n=n->next) {
		if (n->type != XML_ELEMENT_NODE) {
			continue;
		}

		std::string name(reinterpret_cast<const char *>(n->name));
		if (n->type != XML_ELEMENT_NODE) {
			continue;
		}

		get_attributes(n, attr_m);

		if (name == "type") {
//			field_t = elaborate_type(n, attr_m);
		} else {
			fprintf(stdout, "Error: unhandled field element %s\n", name.c_str());
		}
	}

	field = m_model->mkField(attr.at("name"), field_t, field_attr);

	return field;
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

	for (xmlNode *n=p->children; n; n=n->next) {
		if (n->type != XML_ELEMENT_NODE) {
			continue;
		}
		std::string name(reinterpret_cast<const char *>(n->name));
		get_attributes(n, attr_m);

		if (name == "action") {
		} else if (name == "struct") {
		} else {
			fprintf(stdout, "Error: unhandled package element %s\n",
					name.c_str());
		}
	}
}

void XML2PSI::enter_unhandled(const std::string &tag, const strmap &attr) {
	push(0); // push a nop
}

void XML2PSI::enter_action(const strmap &attr) {
	IAction *super = 0;

	if (attr.find("super") != attr.end()) {
		// TODO: look up super
	}

	IAction *action = m_model->mkAction(
			attr.find("name")->second, super);
	PSIUtil::toScopeItem(top())->add(action);
	push(action);
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

	static_cast<IField *>(top())->setDataType(type);
	push(type);
}

void XML2PSI::enter_component(const strmap &attr) {
	IComponent *comp = m_model->mkComponent(attr.find("name")->second);

	PSIUtil::toScopeItem(top())->add(comp);
	push(comp);
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
		} else if (type->second == "lock") {
			field_attr = IField::FieldAttr_Lock;
		} else if (type->second == "share") {
			field_attr = IField::FieldAttr_Share;
		} else if (type->second == "pool") {
			field_attr = IField::FieldAttr_Pool;
		} else {
			// TODO: Error
		}
	}

	IField *field = m_model->mkField(attr.at("name"), 0, field_attr);

	PSIUtil::toScopeItem(top())->add(field);
	push(field);
}

void XML2PSI::enter_literal(const strmap &attr) {
	strmap::const_iterator type_i = attr.find("type");
	strmap::const_iterator value_i = attr.find("value");

	// TODO:
	push(0);
}

void XML2PSI::enter_package(const strmap &attr) {
	std::string name;

	if (attr.find("name") != attr.end()) {
		name = attr.find("name")->second;
	}

	if (name == "") {
		push(m_model->getGlobalPackage());
	} else {
		push(m_model->findPackage(name, true));
	}
}

void XML2PSI::enter_struct_type(const strmap &attr) {
	std::string type = attr.find("type")->second;
	IBaseItem *type_h = 0;

	std::vector<std::string> path = split_path(type);

	IBaseItem *p = pop(); // parent -- probably a field
	IScopeItem *s = PSIUtil::toScopeItem(top());
	push(p); // replace the parent

	type_h = find_type(s, path);

	if (top()->getType() == IBaseItem::TypeField) {
		static_cast<IField *>(top())->setDataType(type_h);
		push(type_h);
	} else {
		// not a field
		fprintf(stdout, "Error: Field not found on the stack\n");
	}
}

void XML2PSI::enter_struct(const strmap &attr) {
	strmap::const_iterator name_it = attr.find("name");
	strmap::const_iterator super_it = attr.find("super");
	strmap::const_iterator type_it = attr.find("type");
	std::string name;
	IStruct *super=0;
	IStruct::StructType type=IStruct::Base;

	if (type_it != attr.end()) {
		if (type_it->second == "memory") {
			type = IStruct::Memory;
		} else if (type_it->second == "stream") {
			type = IStruct::Stream;
		} else if (type_it->second == "state") {
			type = IStruct::State;
		} else if (type_it->second == "resource") {
			type = IStruct::Resource;
		} else {
			// TODO: Error handling
		}
	}

	IStruct *s = m_model->mkStruct(name, type, super);
	IScopeItem *scope = PSIUtil::toScopeItem(top());

	if (scope) {
		scope->add(s);
		push(s);
	} else {
		fprintf(stdout, "top %p %d is not a scope\n",
				top(), top()->getType());
	}
}

void XML2PSI::start(const std::string &el, const char **attr) {
	strmap attr_m;

	for (int i=0; attr[i]; i+=2) {
		attr_m.insert(strmap_ent(attr[i], attr[i+1]));
	}

	if (el == "model") {
		push(m_model);
	} else if (el == "action") {
		enter_action(attr_m);
	} else if (el == "bit" || el == "int") {
		enter_bit_int_type((el == "bit"), attr_m);
	} else if (el == "component") {
		enter_component(attr_m);
	} else if (el == "literal") {
		enter_literal(attr_m);
	} else if (el == "null") {
		push(0);
	} else if (el == "package") {
		enter_package(attr_m);
	} else if (el == "field") {
		enter_field(attr_m);
	} else if (el == "struct") {
		if (top()->getType() == IBaseItem::TypeField) {
			// Scope is <type>
			enter_struct_type(attr_m);
		} else {
			enter_struct(attr_m);
		}
	} else {
		enter_unhandled(el, attr_m);
		push(0);
	}
}

void XML2PSI::end(const std::string &el) {
	pop();
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

void XML2PSI::push(IBaseItem *it) {
	m_scope_stack.push(it);
}

IBaseItem *XML2PSI::pop() {
	IBaseItem *ret = m_scope_stack.top();
	m_scope_stack.pop();
	return ret;
}

IBaseItem *XML2PSI::top() {
	return m_scope_stack.top();
}

void XML2PSI::get_attributes(xmlNode *n, strmap &attr_m) {
	attr_m.clear();

	for (xmlAttrPtr attr=n->properties; attr; attr=attr->next) {
		std::string name = reinterpret_cast<const char *>(attr->name);
		std::string value = reinterpret_cast<const char *>(xmlGetProp(n, attr->name));
		attr_m.insert(strmap_ent(name, value));
	}
}

}
} /* namespace psi */
