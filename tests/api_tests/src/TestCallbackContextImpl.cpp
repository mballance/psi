/*
 * TestCallbackContextImpl.cpp
 *
 *  Created on: Aug 8, 2016
 *      Author: ballance
 */

#include "TestCallbackContextImpl.h"
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>
#include "api/IModel.h"
#include "api/IAction.h"


TestCallbackContextImpl::TestCallbackContextImpl() {
	m_root = 0;
	m_model = 0;
	m_comp = 0;
	m_debug_en = 0;
	m_chandle_testmode = false;
}

TestCallbackContextImpl::~TestCallbackContextImpl() {
	// TODO Auto-generated destructor stub
}

void TestCallbackContextImpl::init(
		const std::string 		&initial,
		IModel					*model,
		IComponent				*comp) {
//	LIBXML_TEST_VERSION

	m_model = model;
	m_comp = comp;

	if (m_root) {
		delete m_root;
	}

	m_root = new ValueNode(m_comp);

	xmlDocPtr doc = xmlReadMemory(
			initial.c_str(),
			initial.length(),
			"initial.xml",
			0,
			0);

	xmlNode *n = xmlDocGetRootElement(doc);

	for (; n; n=n->next) {
		if (n->type != XML_ELEMENT_NODE) {
			continue;
		}

		std::string name;
		name.append(reinterpret_cast<const char *>(n->name));

		if (name == "values") {
			xmlNode *v = n->children;

			for (; v; v=v->next) {
				if (v->type != XML_ELEMENT_NODE) {
					continue;
				}

				name.clear();
				name.append(reinterpret_cast<const char *>(v->name));

				std::string path;

				for (xmlAttrPtr attr=v->properties; attr; attr=attr->next) {
					std::string aname = reinterpret_cast<const char *>(attr->name);
					if (aname == "path") {
						path = reinterpret_cast<const char *>(xmlGetProp(v, attr->name));
					}
				}

				if (path == "") {
					error("Missing 'path' attribute");
				}

				std::vector<std::string> path_l = split_path(path);

				std::string value;
				for (xmlNode *vt=v->children; vt; vt=vt->next) {
					if (vt->type == XML_TEXT_NODE) {
						value = reinterpret_cast<const char *>(vt->content);
						break;
					}
				}

				if (name == "bit") {
					add_bit_node(path_l, toBitValue(value));
				} else if (name == "int") {
					add_int_node(path_l, toIntValue(value));
				} else if (name == "bool") {
					add_bool_node(path_l, (value == "true"));
				} else if (name == "string") {
					add_string_node(path_l, value);
				} else if (name == "chandle") {
					add_chandle_node(path_l, toChandleValue(value));
				} else {
					error("Expect value elements int|bit|string|chandle ; Receive %s", name.c_str());
				}
			}

		} else {
			error("Expect root element <values>; Receive %s", name.c_str());
			return;
		}
	}

}

std::string TestCallbackContextImpl::toString() {
	std::string ret;

	if (m_root) {
		ret += "<values>\n";
		for (std::vector<ValueNode *>::const_iterator it=m_root->m_children.begin();
				it!=m_root->m_children.end(); it++) {
			toString(ret, m_root->m_name, *it);
		}
		ret += "</values>\n";
	}

	return ret;
}

psshandle_t TestCallbackContextImpl::getActionNode() {
	if (m_root && m_root->m_children.size() > 0) {
		return reinterpret_cast<psshandle_t>(m_root->m_children.at(0));
	} else {
		return 0; // Error
	}
}

void TestCallbackContextImpl::toString(
		std::string							&ret,
		const std::string					&name,
		TestCallbackContextImpl::ValueNode	*n) {
	char tmp[64];

	if (n->m_type == ValueNode::ValueNode_Scope) {
		for (std::vector<ValueNode *>::const_iterator it=n->m_children.begin();
				it!=n->m_children.end(); it++) {
			toString(ret, name + "." + n->m_name, *it);
		}
	} else {
		switch (n->m_type) {
		case ValueNode::ValueNode_Bit: {
			sprintf(tmp, "0x%016llx", (unsigned long long)n->m_val.ui64);
			ret.append("    <bit path=\"" + name + "." + n->m_name + "\">");
			ret.append(tmp);
			ret.append("</bit>\n");
		} break;

		case ValueNode::ValueNode_Int: {
			sprintf(tmp, "%d", (long long)n->m_val.i64);
			ret.append("    <int path=\"" + name + "." + n->m_name + "\">");
			ret.append(tmp);
			ret.append("</int>\n");
		}
		break;

		case ValueNode::ValueNode_Bool: {
			ret.append("    <bool path=\"" + name + "." + n->m_name + "\">");
			ret.append((n->m_val.ui64)?"true":"false");
			ret.append("</bool>\n");
		} break;

		case ValueNode::ValueNode_Chandle: {
			ret.append("    <chandle path=\"" + name + "." + n->m_name + "\">");
			if (m_chandle_testmode) {
				ret.append((n->m_val.chandle)?"1":"0");
			} else {
				sprintf(tmp, "%p", n->m_val.chandle);
				ret.append(tmp);
			}
			ret.append("</chandle>\n");
		} break;

		case ValueNode::ValueNode_String: {
			ret.append("    <string path=\"" + name + "." + n->m_name + "\">");
			ret.append((*n->m_val.str));
			ret.append("</string>\n");
		} break;

		default:
			ret.append("    <unknown path=\"" + name + "." + n->m_name + "\"/>");
		}
	}
}


int64_t TestCallbackContextImpl::getIntField(
		psshandle_t 	hndl,
		IField 			*field) {
	ValueNode *n = reinterpret_cast<ValueNode *>(hndl);
	ValueNode *field_n = 0;

	for (std::vector<ValueNode *>::const_iterator it=n->m_children.begin();
			it!=n->m_children.end(); it++) {
		if ((*it)->m_type_h == field) {
			field_n = *it;
			break;
		}
	}

	if (!field_n) {
		error("Failed to obtain field %s from scope %s",
				field->getName().c_str(),
				n->m_name.c_str());
		return 0;
	} else {
		return field_n->m_val.i64;
	}
}

void TestCallbackContextImpl::setIntField(
		psshandle_t 	hndl,
		IField 			*field,
		int64_t 		v) {
	ValueNode *n = reinterpret_cast<ValueNode *>(hndl);
	ValueNode *field_n = 0;

	for (std::vector<ValueNode *>::const_iterator it=n->m_children.begin();
			it!=n->m_children.end(); it++) {
		if ((*it)->m_type_h == field) {
			field_n = *it;
			break;
		}
	}

	if (!field_n) {
		error("Failed to obtain field %s from scope %s",
				field->getName().c_str(),
				n->m_name.c_str());
	} else {
		field_n->m_val.i64 = v;
	}
}

uint64_t TestCallbackContextImpl::getBitField(
		psshandle_t 	hndl,
		IField 			*field) {
	ValueNode *n = reinterpret_cast<ValueNode *>(hndl);
	ValueNode *field_n = 0;

	for (std::vector<ValueNode *>::const_iterator it=n->m_children.begin();
			it!=n->m_children.end(); it++) {
		if ((*it)->m_type_h == field) {
			field_n = *it;
			break;
		}
	}

	if (!field_n) {
		error("Failed to obtain field %s from scope %s",
				field->getName().c_str(),
				n->m_name.c_str());
		return 0;
	} else {
		return field_n->m_val.ui64;
	}
}

void TestCallbackContextImpl::setBitField(
		psshandle_t 	hndl,
		IField 			*field,
		uint64_t 		v) {
	ValueNode *n = reinterpret_cast<ValueNode *>(hndl);
	ValueNode *field_n = 0;

	for (std::vector<ValueNode *>::const_iterator it=n->m_children.begin();
			it!=n->m_children.end(); it++) {
		if ((*it)->m_type_h == field) {
			field_n = *it;
			break;
		}
	}

	if (!field_n) {
		error("Failed to obtain field %s from scope %s",
				field->getName().c_str(),
				n->m_name.c_str());
	} else {
		field_n->m_val.ui64 = v;
	}
}

void TestCallbackContextImpl::setBoolField(
		psshandle_t 	hndl,
		IField 			*field,
		bool 			v) {
	ValueNode *n = reinterpret_cast<ValueNode *>(hndl);
	ValueNode *field_n = 0;

	for (std::vector<ValueNode *>::const_iterator it=n->m_children.begin();
			it!=n->m_children.end(); it++) {
		if ((*it)->m_type_h == field) {
			field_n = *it;
			break;
		}
	}

	if (!field_n) {
		error("Failed to obtain field %s from scope %s",
				field->getName().c_str(),
				n->m_name.c_str());
	} else {
		field_n->m_val.ui64 = v;
	}
}

bool TestCallbackContextImpl::getBoolField(
		psshandle_t 	hndl,
		IField 			*field) {
	ValueNode *n = reinterpret_cast<ValueNode *>(hndl);
	ValueNode *field_n = 0;

	for (std::vector<ValueNode *>::const_iterator it=n->m_children.begin();
			it!=n->m_children.end(); it++) {
		if ((*it)->m_type_h == field) {
			field_n = *it;
			break;
		}
	}

	if (!field_n) {
		error("Failed to obtain field %s from scope %s",
				field->getName().c_str(),
				n->m_name.c_str());
		return 0;
	} else {
		return (field_n->m_val.ui64)?true:false;
	}
}

void *TestCallbackContextImpl::getChandleField(
		psshandle_t 	hndl,
		IField 			*field) {
	ValueNode *n = reinterpret_cast<ValueNode *>(hndl);
	ValueNode *field_n = 0;

	for (std::vector<ValueNode *>::const_iterator it=n->m_children.begin();
			it!=n->m_children.end(); it++) {
		if ((*it)->m_type_h == field) {
			field_n = *it;
			break;
		}
	}

	if (!field_n) {
		error("Failed to obtain field %s from scope %s",
				field->getName().c_str(),
				n->m_name.c_str());
		return 0;
	} else {
		return field_n->m_val.chandle;
	}
}

void TestCallbackContextImpl::setChandleField(
		psshandle_t 	hndl,
		IField 			*field,
		void 			*v) {
	ValueNode *n = reinterpret_cast<ValueNode *>(hndl);
	ValueNode *field_n = 0;

	for (std::vector<ValueNode *>::const_iterator it=n->m_children.begin();
			it!=n->m_children.end(); it++) {
		if ((*it)->m_type_h == field) {
			field_n = *it;
			break;
		}
	}

	if (!field_n) {
		error("Failed to obtain field %s from scope %s",
				field->getName().c_str(),
				n->m_name.c_str());
	} else {
		field_n->m_val.chandle = v;
	}
}

std::string TestCallbackContextImpl::getStringField(
		psshandle_t 	hndl,
		IField 			*field) {
	ValueNode *n = reinterpret_cast<ValueNode *>(hndl);
	ValueNode *field_n = 0;

	for (std::vector<ValueNode *>::const_iterator it=n->m_children.begin();
			it!=n->m_children.end(); it++) {
		if ((*it)->m_type_h == field) {
			field_n = *it;
			break;
		}
	}

	if (!field_n) {
		error("Failed to obtain field %s from scope %s",
				field->getName().c_str(),
				n->m_name.c_str());
		return "";
	} else {
		return (*field_n->m_val.str);
	}
}

void TestCallbackContextImpl::setStringField(
		psshandle_t 		hndl,
		IField 				*field,
		const std::string 	&v) {
	ValueNode *n = reinterpret_cast<ValueNode *>(hndl);
	ValueNode *field_n = 0;

	for (std::vector<ValueNode *>::const_iterator it=n->m_children.begin();
			it!=n->m_children.end(); it++) {
		if ((*it)->m_type_h == field) {
			field_n = *it;
			break;
		}
	}

	if (!field_n) {
		error("Failed to obtain field %s from scope %s",
				field->getName().c_str(),
				n->m_name.c_str());
	} else {
		(*field_n->m_val.str) = v;
	}
}

/**
 * Returns the psshandle_t handle for a field of type struct or action
 */
psshandle_t TestCallbackContextImpl::getHandleField(
		psshandle_t 		hndl,
		IField 				*field) {
	return 0;
}

//ValueNode *TestCallbackContextImpl::findNode(
//		ValueNode 							*n,
//		const std::vector<std::string>		&path,
//		uint32_t							idx,
//		bool 								create) {
//	ValueNode *ret = 0;
//
//
//	return ret;
//}

void TestCallbackContextImpl::log(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	fprintf(stdout, "CallbackContextTrace: ");
	vfprintf(stdout, fmt, ap);
	fprintf(stdout, "\n");

	va_end(ap);
}

void TestCallbackContextImpl::info(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	fprintf(stdout, "Info: ");
	vfprintf(stdout, fmt, ap);
	fprintf(stdout, "\n");

	va_end(ap);
}

void TestCallbackContextImpl::error(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	fprintf(stdout, "Error: ");
	vfprintf(stdout, fmt, ap);
	fprintf(stdout, "\n");

	va_end(ap);
}

void TestCallbackContextImpl::debug(const char *fmt, ...) {
	va_list ap;

	if (m_debug_en) {
		va_start(ap, fmt);

		fprintf(stdout, "CallbackContextTrace: ");
		vfprintf(stdout, fmt, ap);
		fprintf(stdout, "\n");

		va_end(ap);
	}
}

std::vector<std::string> TestCallbackContextImpl::split_path(const std::string &path) {
	std::vector<std::string> ret;

	size_t idx=0, next_p=0;

	while ((next_p=path.find('.', idx)) != std::string::npos) {
		ret.push_back(path.substr(idx, next_p-idx));
		idx = next_p+1;
	}

	if (idx < path.length()) {
		ret.push_back(path.substr(idx, path.length()-idx));
	}

	return ret;
}

TestCallbackContextImpl::ValueNode *TestCallbackContextImpl::get_insert_point(
		const std::vector<std::string>	&path) {
	IScopeItem *s = m_comp;
	ValueNode  *sn = m_root;
	ValueNode  *ret = 0;

	for (std::vector<std::string>::const_iterator it=path.begin();
			it!=path.end(); it++) {
		debug("  path elem=%s", (*it).c_str());
	}

	// First element is the root component

	// Second element will be an action type
	IAction *a = 0;
	for (std::vector<IBaseItem *>::const_iterator it=s->getItems().begin();
			it!=s->getItems().end(); it++) {
		if ((*it)->getType() == IBaseItem::TypeAction &&
				dynamic_cast<IAction *>(*it)->getName() == path.at(1)) {
			a = dynamic_cast<IAction *>(*it);
			break;
		}
	}

	if (!a) {
		error("Failed to find action %s", path.at(1).c_str());
		debug("<-- add_bit_node (failed to find action)");
		return 0;
	}

	// See if the action scope is present in the value-node tree
	bool found = false;
	for (std::vector<ValueNode *>::const_iterator it=sn->m_children.begin();
			it!=sn->m_children.end(); it++) {
		if ((*it)->m_type_h == a) {
			sn = *it;
			found = true;
			break;
		}
	}

	if (!found) {
		ValueNode *new_node = new ValueNode(a);
		sn->m_children.push_back(new_node);
		debug("   Add action node %s to %s",
				new_node->m_name.c_str(),
				sn->m_name.c_str());
		sn = new_node;
	}
	s = a;

	ValueNode *a_n = 0;
	for (std::vector<ValueNode *>::const_iterator it=sn->m_children.begin();
			it!=sn->m_children.end(); it++) {
		IBaseItem *bi_s = dynamic_cast<IBaseItem *>(s);
		if ((*it)->m_type_h == bi_s) {
			a_n = (*it);
			break;
		}
	}

	if (!a_n) {
		a_n = new ValueNode(s);
		sn->m_children.push_back(a_n);
		debug("   Add action node %s to %s",
				a_n->m_name.c_str(),
				sn->m_name.c_str());
	}

	if (path.size() <= 3) {
		ret = sn;
	}

	// Third and beyond will be fields
	for (uint32_t i=2; i<path.size()-1; i++) {
		std::string field_name = path.at(i);
		ValueNode *fn = 0;
		IField *field = 0;

		// See a node already exists
		for (std::vector<ValueNode *>::const_iterator it=sn->m_children.begin();
				it!=sn->m_children.end(); it++) {
			if ((*it)->m_name == field_name) {
				fn = (*it);
				break;
			}
		}

		// Find the corresponding type field
		if (!fn) {
			for (std::vector<IBaseItem *>::const_iterator it=s->getItems().begin();
					it!=s->getItems().end(); it++) {
				IBaseItem *item = *it;

				if ((field = dynamic_cast<IField*>(item)) &&
						field->getName() == field_name) {
					break;
				} else {
					field = 0;
				}
			}

			if (!field) {
				error("Failed to find type field %s in scope %s",
						field_name.c_str(),
						dynamic_cast<INamedItem *>(s)->getName().c_str());
				break;
			} else {
				// on the way to the leaf

				fn = new ValueNode(field);
				sn->m_children.push_back(fn);
				if (i+2>=path.size()) {
					ret = fn;
					break;
				} else {
					if (!(s = dynamic_cast<IScopeItem *>(field->getDataType()))) {
						error("Failed to get type-scope for field %s", field_name.c_str());
					}
				}
			}
		}
	}

	return ret;
}

void TestCallbackContextImpl::add_bit_node(
		const std::vector<std::string>	&path,
		uint64_t						val) {
	debug("--> add_bit_node");
	ValueNode *n = get_insert_point(path);

	IScopeItem *s = 0;
	if (n->m_type_h->getType() == IBaseItem::TypeField) {
		// Parent is a composite field
		s = dynamic_cast<IScopeItem *>(
				dynamic_cast<IField *>(n->m_type_h)->getDataType());
	} else {
		// Parent is an action/struct
		s = dynamic_cast<IScopeItem *>(n->m_type_h);
	}

	IField *f = 0;

	const std::string &field_name = path.at(path.size()-1);
	for (std::vector<IBaseItem *>::const_iterator it=s->getItems().begin();
			it!=s->getItems().end(); it++) {
		IBaseItem *t = *it;

		if (t->getType() == IBaseItem::TypeField &&
				dynamic_cast<IField *>(t)->getName() == field_name) {
			f = dynamic_cast<IField *>(t);
			break;
		}
	}

	if (!f) {
		error("Failed to find field %s", field_name.c_str());
		return;
	}

	n->m_children.push_back(new ValueNode(f, val));

	debug("<-- add_bit_node");
}

void TestCallbackContextImpl::add_int_node(
		const std::vector<std::string>	&path,
		int64_t							val) {
	debug("--> add_int_node");
	ValueNode *n = get_insert_point(path);

	IScopeItem *s = 0;
	if (n->m_type_h->getType() == IBaseItem::TypeField) {
		// Parent is a composite field
		s = dynamic_cast<IScopeItem *>(
				dynamic_cast<IField *>(n->m_type_h)->getDataType());
	} else {
		// Parent is an action/struct
		s = dynamic_cast<IScopeItem *>(n->m_type_h);
	}

	IField *f = 0;

	const std::string &field_name = path.at(path.size()-1);
	for (std::vector<IBaseItem *>::const_iterator it=s->getItems().begin();
			it!=s->getItems().end(); it++) {
		IBaseItem *t = *it;

		if (t->getType() == IBaseItem::TypeField &&
				dynamic_cast<IField *>(t)->getName() == field_name) {
			f = dynamic_cast<IField *>(t);
			break;
		}
	}

	if (!f) {
		error("Failed to find field %s", field_name.c_str());
		return;
	}

	n->m_children.push_back(new ValueNode(f, val));

	debug("<-- add_int_node");
}

void TestCallbackContextImpl::add_bool_node(
		const std::vector<std::string>	&path,
		bool							val) {
	debug("--> add_int_node");
	ValueNode *n = get_insert_point(path);

	IScopeItem *s = 0;
	if (n->m_type_h->getType() == IBaseItem::TypeField) {
		// Parent is a composite field
		s = dynamic_cast<IScopeItem *>(
				dynamic_cast<IField *>(n->m_type_h)->getDataType());
	} else {
		// Parent is an action/struct
		s = dynamic_cast<IScopeItem *>(n->m_type_h);
	}

	IField *f = 0;

	const std::string &field_name = path.at(path.size()-1);
	for (std::vector<IBaseItem *>::const_iterator it=s->getItems().begin();
			it!=s->getItems().end(); it++) {
		IBaseItem *t = *it;

		if (t->getType() == IBaseItem::TypeField &&
				dynamic_cast<IField *>(t)->getName() == field_name) {
			f = dynamic_cast<IField *>(t);
			break;
		}
	}

	if (!f) {
		error("Failed to find field %s", field_name.c_str());
		return;
	}

	n->m_children.push_back(new ValueNode(f, val));

	debug("<-- add_int_node");
}

void TestCallbackContextImpl::add_string_node(
		const std::vector<std::string>	&path,
		const std::string 				&val) {
	debug("--> add_int_node");
	ValueNode *n = get_insert_point(path);

	IScopeItem *s = 0;
	if (n->m_type_h->getType() == IBaseItem::TypeField) {
		// Parent is a composite field
		s = dynamic_cast<IScopeItem *>(
				dynamic_cast<IField *>(n->m_type_h)->getDataType());
	} else {
		// Parent is an action/struct
		s = dynamic_cast<IScopeItem *>(n->m_type_h);
	}

	IField *f = 0;

	const std::string &field_name = path.at(path.size()-1);
	for (std::vector<IBaseItem *>::const_iterator it=s->getItems().begin();
			it!=s->getItems().end(); it++) {
		IBaseItem *t = *it;

		if (t->getType() == IBaseItem::TypeField &&
				dynamic_cast<IField *>(t)->getName() == field_name) {
			f = dynamic_cast<IField *>(t);
			break;
		}
	}

	if (!f) {
		error("Failed to find field %s", field_name.c_str());
		return;
	}

	n->m_children.push_back(new ValueNode(f, val));

	debug("<-- add_int_node");
}

void TestCallbackContextImpl::add_chandle_node(
		const std::vector<std::string>	&path,
		void							*val) {
	debug("--> add_int_node");
	ValueNode *n = get_insert_point(path);

	IScopeItem *s = 0;
	if (n->m_type_h->getType() == IBaseItem::TypeField) {
		// Parent is a composite field
		s = dynamic_cast<IScopeItem *>(
				dynamic_cast<IField *>(n->m_type_h)->getDataType());
	} else {
		// Parent is an action/struct
		s = dynamic_cast<IScopeItem *>(n->m_type_h);
	}

	IField *f = 0;

	const std::string &field_name = path.at(path.size()-1);
	for (std::vector<IBaseItem *>::const_iterator it=s->getItems().begin();
			it!=s->getItems().end(); it++) {
		IBaseItem *t = *it;

		if (t->getType() == IBaseItem::TypeField &&
				dynamic_cast<IField *>(t)->getName() == field_name) {
			f = dynamic_cast<IField *>(t);
			break;
		}
	}

	if (!f) {
		error("Failed to find field %s", field_name.c_str());
		return;
	}

	n->m_children.push_back(new ValueNode(f, val));

	debug("<-- add_int_node");
}

uint64_t TestCallbackContextImpl::toBitValue(const std::string &v) {
	return strtoull(v.c_str(), 0, 0);
}

int64_t TestCallbackContextImpl::toIntValue(const std::string &v) {
	return strtoll(v.c_str(), 0, 0);
}

void *TestCallbackContextImpl::toChandleValue(const std::string &v) {
	return reinterpret_cast<void *>(strtoull(v.c_str(), 0, 0));
}

TestCallbackContextImpl::ValueNode::ValueNode(IScopeItem *scope) {
	m_type    = ValueNode_Scope;
	m_type_h  = dynamic_cast<IBaseItem *>(scope);
	m_name    = dynamic_cast<INamedItem *>(scope)->getName();
	m_val.str = 0;
}

TestCallbackContextImpl::ValueNode::ValueNode(IField *field) {
	m_type    = ValueNode_ScopeField;
	m_type_h  = field;
	m_name    = field->getName();
	m_val.str = 0;
}

TestCallbackContextImpl::ValueNode::ValueNode(IField *field, uint64_t v) {
	m_type     = ValueNode_Bit;
	m_type_h   = field;
	m_name     = field->getName();
	m_val.ui64 = v;
}

TestCallbackContextImpl::ValueNode::ValueNode(IField *field, int64_t v) {
	m_type     = ValueNode_Int;
	m_type_h   = field;
	m_name     = field->getName();
	m_val.i64  = v;
}

TestCallbackContextImpl::ValueNode::ValueNode(IField *field, const std::string &v) {
	m_type     = ValueNode_String;
	m_type_h   = field;
	m_name     = field->getName();
	m_val.str  = new std::string();
	(*m_val.str) = v;
}

TestCallbackContextImpl::ValueNode::ValueNode(IField *field, bool v) {
	m_type     = ValueNode_Bool;
	m_type_h   = field;
	m_name     = field->getName();
	m_val.ui64 = (v)?1:0;
}

TestCallbackContextImpl::ValueNode::ValueNode(IField *field, void *v) {
	m_type     = ValueNode_Chandle;
	m_type_h   = field;
	m_name     = field->getName();
	m_val.chandle = v;
}

TestCallbackContextImpl::ValueNode::~ValueNode() {
	if (m_type == ValueNode_String) {
		delete m_val.str;
	}

	for (std::vector<ValueNode *>::const_iterator it=m_children.begin();
			it!=m_children.end(); it++) {
		delete *it;
	}
}

