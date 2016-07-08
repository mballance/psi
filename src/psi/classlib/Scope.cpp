/*
 * Scope.cpp
 *
 *  Created on: Jul 7, 2016
 *      Author: ballance
 */

#include "classlib/Scope.h"
#include "classlib/Model.h"

namespace psi {

Scope::Scope(ScopeType t) : m_scope_type(t) {
	m_type = &typeid(this);
	m_ctxt = 0;
	enter();
}

Scope::~Scope() {
	leave();
}

BaseItem *Scope::parent() const {
	const std::vector<const Scope *> &scope = Model::global()->get_scope();

	// Return the first case where m_parent != this
	for (int i=scope.size()-1; i>=0; i--) {
		if (scope.at(i)->m_ctxt != m_ctxt) {
			return scope.at(i)->m_ctxt;
		}
	}

	return Model::global();
}

const char *Scope::name() const {
	return m_type->name();
}

void Scope::enter() {
//	if (!m_ctxt) {
//		m_ctxt = Model::global();
//	}
//	if (m_ctxt) {
		fprintf(stdout, "--> enter %s %d\n",
				(m_scope_type == ScopeType_FieldDecl)?"FieldDecl":
						(m_scope_type == ScopeType_TypeDecl)?"TypeDecl":"UNKNOWN",
				(m_ctxt)?m_ctxt->getObjectType():-1);
		Model::global()->push_scope(this);
//	}
}

void Scope::leave() {
//	if (m_ctxt) {
		fprintf(stdout, "<-- leave %s %d\n",
				(m_scope_type == ScopeType_FieldDecl)?"FieldDecl":
						(m_scope_type == ScopeType_TypeDecl)?"TypeDecl":"UNKNOWN",
				(m_ctxt)?m_ctxt->getObjectType():-1);
		Model::global()->pop_scope();
//	}
}

} /* namespace psi */
