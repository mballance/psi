/*
 * ModelImp.cpp
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
 *
 *  Created on: Apr 25, 2016
 *      Author: ballance
 */

#include "ModelImp.h"
#include "ScopeImp.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// TODO: header file is GCC-specific
#include <cxxabi.h>

namespace pss {

Model::Model(ModelImp *imp) : BaseItem(imp) {

}

ModelImp::ModelImp() : BaseItemImp(new pss::Model(this), BaseItemImp::Model, 0) {
	m_scopes.push_back(master());
	m_scope.push_back(new ScopeImp(master()));
}

ModelImp::~ModelImp() {
	// TODO Auto-generated destructor stub
}

ModelImp *ModelImp::global() {
	if (!m_global) {
		m_global = new ModelImp();
	}
	return m_global;
}

void ModelImp::push_scope(const ScopeImp *p) {

	fprintf(stdout, "--> push_scope Context: %p %s (%d)\n",
				p->ctxt(), p->scope_name(), (int)(m_scope.size()+1));

	m_scope.push_back(p);
	m_scopes.push_back(p->ctxt());

	// Search back to back-populate 'ctxt' handle
	if (p->ctxt()) {
	int i=m_scope.size()-1;
	std::vector<BaseItem *>::iterator it = m_scopes.end();
	it--;

	for (; i>=0; i--) {
		if (m_scope.at(i)->ctxt() != p->ctxt()) {
			break;
		}
		it--;
	}

	if (i>=0) {
		fprintf(stdout, "Setting parent context: @ %d - %p\n", i, p->ctxt());
		m_scopes.erase(it);
		m_scopes.insert(it, p->ctxt());
	}
	}

	fprintf(stdout, "<-- push_scope Context: %p %s (%d)\n",
				p->ctxt(), p->scope_name(), (int)(m_scope.size()+1));
}

void ModelImp::pop_scope(const ScopeImp *p) {
//	const Scope *p_c = m_scope.back();

	if (p->ctxt()) {
		fprintf(stdout, "-- pop_scope Context: %p (%d)\n",
				p->ctxt(), (int)m_scope.size());
	} else {
		fprintf(stdout, "-- pop_scope Name: %s (%d)\n",
				p->scope_name(), (int)m_scope.size());
	}

	// pss_if the last element is 'p', then pop until
	// we exit that hierarchy
	if (m_scope.size() > 0) {
		m_scope.pop_back();
		m_scopes.pop_back();
//		if (m_scope.back()->ctxt() == p->ctxt()) {
//			m_last_scope = m_scope.back()->ctxt();
//
//			while (m_scope.size() > 0 &&
//					m_scope.back()->ctxt() == p->ctxt()) {
//				const ScopeImp *pp = m_scope.back();
//				//			fprintf(stdout, "  pop-back %p\n", pp->ctxt());
//				m_scope.pop_back();
//			}
//
//			// Update 'm_is_field' state
//			if (m_scope.size() > 0) {
//				m_is_field = m_scope.at(m_scope.size()-1)->is_field();
//			}
//		}
	} else {
		fprintf(stdout, "Error: attempting to pop scope from empty stack\n");
	}
}

const std::vector<const ScopeImp *> &ModelImp::get_scope() const {
	return m_scope;
}

const std::vector<BaseItem *> &ModelImp::get_scopes() const {
	return m_scopes;
}

uint32_t ModelImp::depth() const {
	return m_scope.size();
}

TypePathImp ModelImp::getActiveTypeName(BaseItem *it) {
	const ScopeImp *scope = 0;
//	fprintf(stdout, "--> getActiveTypeName\n");
	for (int i=m_scope.size()-1; i>=0; i--) {
//		fprintf(stdout, "m_scope[%d]=%p it=%p\n",
//				i, m_scope.at(i)->ctxt(), it);
		if (m_scope.at(i)->ctxt() == it) {
			scope = m_scope.at(i);
		} else {
			break;
		}
	}

	if (scope) {
		TypePathImp ret = ModelImp::demangle(scope);

//		for (std::vector<std::string>::const_iterator it=ret.get().begin();
//				it!=ret.get().end(); it++) {
//			fprintf(stdout, "  path=%s\n", (*it).c_str());
//		}

		return ret;
	} else {
		fprintf(stdout, "getActiveTypeName: failed to find scope %p\n", it);
		for (uint32_t i=0; i<m_scope.size(); i++) {
			fprintf(stdout, "    scope[%d]=%p\n", i, m_scope.at(i)->ctxt());
		}
		return TypePathImp();
	}
}

BaseItemImp *ModelImp::getActiveType(BaseItem *it) {
	BaseItem *ret = 0;
//	fprintf(stdout, "--> getActiveTypeName %p\n", it);
	for (int i=m_scope.size()-1; i>=0; i--) {
//		fprintf(stdout, "  %p %p\n", m_scope.at(i)->ctxt(), it);
		if (m_scope.at(i)->ctxt() == it) {
			ret = m_scope.at(i)->type_id();
		} else {
			break;
		}
	}

//	fprintf(stdout, "<-- getActiveTypeName %p %p\n", it, ret);
	return (ret)?ret->impl():0;
}

TypePathImp ModelImp::getSuperType(BaseItem *it) {
	// Looking for <last+1>
//	fprintf(stdout, "--> getSuperType %p\n", it);
	int i=0;
	for (i=m_scopes.size()-1; i>=0; i--) {
//		fprintf(stdout, "m_scopes[%d]=%p it=%p\n", i, m_scopes.at(i), it);
		if (m_scopes.at(i) != it) {
			// The 'leaf' is actually the next one
			i++;
			break;
		}
	}

	// i points to the type
	// i+1 points to the supertype as long as

//	fprintf(stdout, "i=%d scope.size=%d\n", i, (int)m_scope.size());
	if (i >= 0 && m_scope.size() > i+2) {
		const char *name_i = "null";
		const char *name_ip1 = "null";

		if (m_scope.at(i+1)->get_typeinfo()) {
			name_ip1 = m_scope.at(i+1)->get_typeinfo()->name();
		}
		if (m_scope.at(i)->get_typeinfo()) {
			name_i = m_scope.at(i)->get_typeinfo()->name();
		}
//		fprintf(stdout, "scope[i+1]=%s scope[i]=%s\n", name_ip1, name_i);
		if (m_scope.at(i+1)->get_typeinfo() != m_scope.at(i)->get_typeinfo()) {
			TypePathImp super = ModelImp::demangle(m_scope.at(i+1));

			for (std::vector<std::string>::const_iterator it=super.get().begin();
					it!=super.get().end(); it++) {
//				fprintf(stdout, "  path=%s\n", (*it).c_str());
			}

			return super;
		}
	}
//	fprintf(stdout, "<-- getSuperType\n");

	return TypePathImp();
}

BaseItem *ModelImp::getParentScope() {
	BaseItem *p = 0;

	fprintf(stdout, "--> getParentScope\n");

	if (m_scopes.size() > 0) {
		BaseItem *s = m_scopes.at(m_scopes.size()-1);

		for (int32_t i=m_scopes.size()-1; i>=0; i--) {
			fprintf(stdout, "  Searching: %p %p\n", m_scopes.at(i), s);
			if (m_scopes.at(i) != s/* || (!include_fields && m_scope.at(i)->is_field())*/) {
				p = m_scopes.at(i);
				break;
			}
		}
	}

	fprintf(stdout, "<-- getParentScope %p\n", p);

	return p;
}

bool ModelImp::isField() {
	return is_field();
}

bool ModelImp::isParentField() {
	bool ret = false;

	if (m_scopes.size() > 0) {
		BaseItem *s = m_scopes.at(m_scopes.size()-1);

		for (int32_t i=m_scopes.size()-1; i>=0; i--) {
			fprintf(stdout, "  Searching: %p %p\n", m_scopes.at(i), s);
			if (m_scopes.at(i) != s) {
				ret = m_scope.at(i)->is_field();
				break;
			}
		}
	}

	return ret;
}

BaseItem *ModelImp::getActiveScope() {
//	fprintf(stdout, "ModelImp::getActiveScope scope=%d\n",
//			(m_last_scope)?m_last_scope->getObjectType():-1);

//	if (m_is_field) {
//		return 0;
//	} else {
		// Search back until we find something different than 'us'
		BaseItem *curr = (m_scopes.size())?m_scopes.at(m_scopes.size()-1):0;

		for (int i=m_scopes.size()-1; i>=0; i--) {
			if (m_scopes.at(i) != curr) {
				curr = m_scopes.at(i);
				break;
			}
		}

		if (!curr) {
			return ModelImp::global()->master();
		} else {
			return curr;
		}
//	}

//	fprintf(stdout, "ModelImp::getActiveScope size=%d\n", m_scope.size());
//
//	for (int i=m_scope.size()-1; i>=0; i--) {
//		fprintf(stdout, "  %d %p it=%p\n", i, m_scope.at(i)->ctxt(), it);
//		if (m_scope.at(i)->ctxt() && m_scope.at(i)->ctxt() != it) {
//			fprintf(stdout, "Returning %d\n", m_scope.at(i)->ctxt()->getObjectType());
//			return m_scope.at(i)->ctxt();
//		}
//	}
//
//	return 0;
}

const char *ModelImp::get_field_name(BaseItem *p) {
	const char *ret = 0;
	fprintf(stdout, "--> get_field_name\n");

	print_scopes();

	// Just pick the last scope that specified a name
	for (int i=m_scope.size()-1; i>=0; i--) {
		if (m_scope.at(i)->is_field()) {
			ret = m_scope.at(i)->scope_name();
			break;
		} else if (m_scope.at(i)->is_type()) {
			m_tmpname = demangle(m_scope.at(i+1)).leaf();
			ret = m_tmpname.c_str();
			break;
		}
//		if (!m_scope.at(i)->ctxt() &&
//				m_scope.at(i)->scope_name() &&
//				strcmp(m_scope.at(i)->scope_name(), "") != 0) {
//			fprintf(stdout, "<-- get_field_name %s\n", m_scope.at(i)->scope_name());
//			return m_scope.at(i)->scope_name();
//		}
	}

	fprintf(stdout, "<-- get_field_name %s\n", ret);
	return ret;
}

bool ModelImp::is_field() const {
	for (int i=m_scope.size()-1; i>=0; i--) {
		if (m_scope.at(i)->is_field()) {
			return true;
		}
	}

	return false;
}

TypePathImp ModelImp::demangle(const ScopeImp *s) {
	TypePathImp name;
	const std::type_info *info = s->get_typeinfo();

    char *n = abi::__cxa_demangle(info->name(), 0, 0, 0);

//    fprintf(stdout, "--> n=%s\n", n);

    char *r = n;
    int nl = strlen(n);

    // Forget about pointer
    char *tp = &n[nl-1];
    if (n[nl-1] == '*') {
            n[nl-1] = 0;
            tp--;
    }

    // Accumulate name elements, while killing template specializations
    int bk=0;
    while (tp > n) {
            if (*tp == '>') {
                    bk++;
            } else if (*tp == '<') {
                    bk--;
                    if (bk == 0) {
                            *tp = 0;
                    }
            } else if (*tp == ':' && bk == 0) {
                    name.prepend(tp+1);

                    if (tp > 0) {
                            tp--;
                            if (*tp == ':') {
                                    *tp = 0;
                            }
                    }
                    break;
            }
            tp--;
    }

    name.prepend(n);

    free(n);

    return name;
}

BaseItem *ModelImp::pOrGlobal(BaseItem *p) {
	return (p)?p:ModelImp::global()->master();
}

void ModelImp::print_scopes() {
	ModelImp *m = ModelImp::global();

	fprintf(stdout, "--> print_scopes()\n");
	for (int32_t i=m->m_scope.size()-1; i>=0; i--) {
		const ScopeImp *s = m->m_scope.at(i);
		BaseItem *b = m->m_scopes.at(i);
		fprintf(stdout, "  scope=%p name=%s type_name=%s is_field=%s is_type=%s\n",
				b, s->scope_name(),
				(s->get_typeinfo())?s->get_typeinfo()->name():"NULL",
				(s->is_field())?"true":"false",
				(s->is_type())?"true":"false");
	}
	fprintf(stdout, "<-- print_scopes()\n");
}

ModelImp *ModelImp::m_global = 0;

} /* namespace pss */
