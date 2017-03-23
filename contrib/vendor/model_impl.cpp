/*
 * model_impl.cpp
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// TODO: header file is GCC-specific
#include <cxxabi.h>
#include "model_impl.h"
#include "scope.h"

namespace pss {
namespace vendor {

model_impl::model_impl() : base_item(base_item::Model, 0) {
	m_scopes.push_back(this);
	m_scope.push_back(new scope(this));
}

model_impl::~model_impl() {
	// TODO Auto-generated destructor stub
}

model_impl *model_impl::global() {
	if (!m_global) {
		m_global = new model_impl();
	}
	return m_global;
}

void model_impl::push_scope(const scope_impl *p) {
	m_scope.push_back(p);
	m_scopes.push_back(p->ctxt());

	// Search back to back-populate 'ctxt' handle
	if (p->ctxt()) {
	int i=m_scope.size()-1;
	std::vector<base_item *>::iterator it = m_scopes.end();
	it--;

	for (; i>=0; i--) {
		if (m_scope.at(i)->ctxt() != p->ctxt()) {
			break;
		}
		it--;
	}

	if (i>=0) {
		m_scopes.erase(it);
		m_scopes.insert(it, p->ctxt());
	}
	}
}

void model_impl::pop_scope(const scope_impl *p) {
	// pss_if the last element is 'p', then pop until
	// we exit that hierarchy
	if (m_scope.size() > 0) {
		m_scope.pop_back();
		m_scopes.pop_back();
	} else {
		fprintf(stdout, "Error: attempting to pop scope_impl from empty stack\n");
	}
}

const std::vector<const scope_impl *> &model_impl::get_scope() const {
	return m_scope;
}

const std::vector<base_item *> &model_impl::get_scopes() const {
	return m_scopes;
}

uint32_t model_impl::depth() const {
	return m_scope.size();
}

type_path model_impl::getActiveTypeName(base_item *it) {
	const scope_impl *scope_impl = 0;
	for (int i=m_scope.size()-1; i>=0; i--) {
		if (m_scope.at(i)->ctxt() == it) {
			scope_impl = m_scope.at(i);
		} else {
			break;
		}
	}

	if (scope_impl) {
		type_path ret = model_impl::demangle(scope_impl);
		return ret;
	} else {
		fprintf(stdout, "getActiveTypeName: failed to find scope_impl %p\n", it);
		for (uint32_t i=0; i<m_scope.size(); i++) {
			fprintf(stdout, "    scope_impl[%d]=%p\n", i, m_scope.at(i)->ctxt());
		}
		return type_path();
	}
}

base_item *model_impl::getActiveType(base_item *it) {
	base_item *ret = 0;
//	fprintf(stdout, "getActiveType: it=%p\n", it);
//	print_scopes();
	for (int i=m_scope.size()-1; i>=0; i--) {
		if (m_scope.at(i)->ctxt() == it && m_scope.at(i)->type_id()) {
			ret = m_scope.at(i)->type_id();
		} else {
			break;
		}
	}

	return ret;
}

type_path model_impl::getSuperType() {
	if (m_scope.size() > 0) {
		base_item *s = m_scope.at(m_scope.size()-1)->ctxt();
		int32_t i=m_scope.size()-1;

		// Super-type will be called from the very base type (action, pss_struct, component)
		// Scan back as long as the context is the same
		for (; i>=0; i--) {
			if (m_scope.at(i)->ctxt() != s) {
				i++;
				break;
			}
		}

		// i now points where the user's type started
		if (i >= 0 && i+1 < m_scope.size()) {
			type_path super = model_impl::demangle(m_scope.at(i+1));
			return super;
		} else {
			return type_path();
		}
	} else {
		return type_path();
	}
}

base_item *model_impl::getParentScope() {
	base_item *p = 0;

	if (m_scopes.size() > 0) {
		base_item *s = m_scopes.at(m_scopes.size()-1);

		for (int32_t i=m_scopes.size()-1; i>=0; i--) {
			if (m_scopes.at(i) != s) {
				p = m_scopes.at(i);
				break;
			}
		}
	}

	return p;
}

bool model_impl::isField() {
	return is_field();
}

bool model_impl::isType() {
	bool ret = false;

	if (m_scopes.size() > 0) {
		base_item *s = m_scopes.at(m_scopes.size()-1);

		for (int32_t i=m_scopes.size()-1; i>=0; i--) {
			if (m_scopes.at(i) != s) {
				ret = m_scope.at(i)->is_type();
				break;
			}
		}
	}

	return ret;
}

bool model_impl::isParentField() {
	bool ret = false;

	if (m_scopes.size() > 0) {
		base_item *s = m_scopes.at(m_scopes.size()-1);

		for (int32_t i=m_scopes.size()-1; i>=0; i--) {
			if (m_scopes.at(i) != s) {
				ret = m_scope.at(i)->is_field();
				break;
			}
		}
	}

	return ret;
}

base_item *model_impl::getActiveScope() {
	// Search back until we find something different than 'us'
	base_item *curr = (m_scopes.size())?m_scopes.at(m_scopes.size()-1):0;

	for (int i=m_scopes.size()-1; i>=0; i--) {
		if (m_scopes.at(i) != curr) {
			curr = m_scopes.at(i);
			break;
		}
	}

	if (!curr) {
		return model_impl::global();
	} else {
		return curr;
	}
}

const char *model_impl::get_field_name() {
	const char *ret = 0;

	// Just pick the last scope_impl that specified a name
	for (int i=m_scope.size()-1; i>=0; i--) {
		if (m_scope.at(i)->is_field()) {
			ret = m_scope.at(i)->scope_name();
			break;
		} else if (m_scope.at(i)->is_type()) {
			m_tmpname = demangle(m_scope.at(i+1)).leaf();
			ret = m_tmpname.c_str();
			break;
		}
	}

	return ret;
}

bool model_impl::is_field() const {
	for (int i=m_scope.size()-1; i>=0; i--) {
		if (m_scope.at(i)->is_field()) {
			return true;
		}
	}

	return false;
}

type_path model_impl::demangle(const scope_impl *s) {
	type_path name;
	const std::type_info *info = s->get_typeinfo();

    char *n = abi::__cxa_demangle(info->name(), 0, 0, 0);

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

base_item *model_impl::pOrGlobal(base_item *p) {
	return (p)?p:model_impl::global();
}

void model_impl::print_scopes() {
	model_impl *m = model_impl::global();

	fprintf(stdout, "--> print_scopes()\n");
	for (int32_t i=m->m_scope.size()-1; i>=0; i--) {
		const scope_impl *s = m->m_scope.at(i);
		base_item *b = m->m_scopes.at(i);
		fprintf(stdout, "  scope_impl=%p name=%s type_name=%s is_field=%s is_type=%s ctxt=%p\n",
				b, s->scope_name(),
				(s->get_typeinfo())?s->get_typeinfo()->name():"NULL",
				(s->is_field())?"true":"false",
				(s->is_type())?"true":"false",
				m->m_scope.at(i)->ctxt());
	}
	fprintf(stdout, "<-- print_scopes()\n");
}

model_impl *model_impl::m_global = 0;

} /* namespace vendor */
} /* namespace pss */
