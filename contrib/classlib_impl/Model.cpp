/*
 * Model.cpp
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
 *
 *  Created on: Apr 25, 2016
 *      Author: ballance
 */

#include "classlib/Model.h"
#include "classlib/Scope.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// TODO: header file is GCC-specific
#include <cxxabi.h>

namespace psi {

Model::Model() : BaseItem(BaseItem::Model),
		m_last_scope(this), m_in_field_decl(false) { }

Model::~Model() {
	// TODO Auto-generated destructor stub
}

Model *Model::global() {
	if (!m_global) {
		m_global = new Model();
	}
	return m_global;
}

void Model::push_scope(const Scope *p) {
	m_scope.push_back(p);

	if (p->ctxt()) {
		m_last_scope = p->ctxt();
	}
	m_in_field_decl = p->in_field_decl();
}

void Model::pop_scope(const Scope *p) {
//	const Scope *p_c = m_scope.back();

	// If the last element is 'p', then pop until
	// we exit that hierarchy
	if (m_scope.back()->ctxt() == p->ctxt()) {
		m_last_scope = m_scope.back()->ctxt();

		while (m_scope.size() > 0 &&
				m_scope.back()->ctxt() == p->ctxt()) {
			const Scope *pp = m_scope.back();
//			fprintf(stdout, "  pop-back %p\n", pp->ctxt());
			m_scope.pop_back();
		}

		// Update 'm_in_field_decl' state
		if (m_scope.size() > 0) {
			m_in_field_decl = m_scope.at(m_scope.size()-1)->in_field_decl();
		}
	}

}

const std::vector<const Scope *> &Model::get_scope() const {
	return m_scope;
}

TypePath Model::getActiveTypeName(BaseItem *it) {
	const Scope *scope = 0;
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
		TypePath ret = Model::demangle(scope);

//		for (std::vector<std::string>::const_iterator it=ret.get().begin();
//				it!=ret.get().end(); it++) {
//			fprintf(stdout, "  path=%s\n", (*it).c_str());
//		}

		return ret;
	}

	return TypePath();
}

TypePath Model::getSuperType(BaseItem *it) {
	// Looking for <last+1>
//	fprintf(stdout, "--> getSuperType\n");
	int i=0;
	for (i=m_scope.size()-1; i>=0; i--) {
//		fprintf(stdout, "m_scope[%d]=%p it=%p\n",
//				i, m_scope.at(i)->ctxt(), it);
		if (m_scope.at(i)->ctxt() != it) {
			// The 'leaf' is actually the next one
			i++;
			break;
		}
	}

//	fprintf(stdout, "i=%d scope.size=%d\n", i, m_scope.size());
	if (m_scope.size() > i+1) {
//		fprintf(stdout, "scope[i+1]=%s scope[i]=%s\n",
//				m_scope.at(i+1)->get_typeinfo()->name(),
//				m_scope.at(i)->get_typeinfo()->name());
		if (m_scope.at(i+1)->get_typeinfo() != m_scope.at(i)->get_typeinfo()) {
			TypePath super = Model::demangle(m_scope.at(i+1));

			for (std::vector<std::string>::const_iterator it=super.get().begin();
					it!=super.get().end(); it++) {
//				fprintf(stdout, "  path=%s\n", (*it).c_str());
			}

			return super;
		}
	}
//	fprintf(stdout, "<-- getSuperType\n");

	return TypePath();
}

BaseItem *Model::getActiveScope() {
//	fprintf(stdout, "Model::getActiveScope scope=%d\n",
//			(m_last_scope)?m_last_scope->getObjectType():-1);

	if (m_in_field_decl) {
		return 0;
	} else {
		// Search back until we find something different than 'us'
		BaseItem *curr = (m_scope.size())?m_scope.at(m_scope.size()-1)->ctxt():0;

		for (int i=m_scope.size()-1; i>=0; i--) {
			if (m_scope.at(i)->ctxt() != curr) {
				curr = m_scope.at(i)->ctxt();
				break;
			}
		}

		if (!curr) {
			return this;
		} else {
			return curr;
		}
	}

//	fprintf(stdout, "Model::getActiveScope size=%d\n", m_scope.size());
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

TypePath Model::demangle(const Scope *s) {
	TypePath name;
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

Model *Model::m_global = 0;

} /* namespace psi */
