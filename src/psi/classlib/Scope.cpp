/*
 * Scope.cpp
 *
 *  Created on: Jul 7, 2016
 *      Author: ballance
 */

#include "classlib/Scope.h"
#include "classlib/Model.h"

namespace psi {

Scope::Scope(bool in_field_decl) : m_in_field_decl(in_field_decl) {
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

void Scope::init(const std::type_info *type, BaseItem *ctxt) {
	m_type = type;
	m_ctxt = ctxt;

	// Propagate current state
	m_in_field_decl = Model::global()->in_field_decl();
//	fprintf(stdout, "Scope::init: %s m_ctxt=%p m_in_field_decl=%s\n",
//			(m_type)?m_type->name():"NULL",
//			m_ctxt, (m_in_field_decl)?"true":"false");
}

void Scope::enter() {
//		fprintf(stdout, "--> enter %s %s %d\n",
//				(m_in_field_decl)?"FieldDecl":"TypeDecl", name(),
//				(m_ctxt)?m_ctxt->getObjectType():-1);
		Model::global()->push_scope(this);
}

void Scope::leave() {
//		fprintf(stdout, "<-- leave %s %s %d\n",
//				(m_in_field_decl)?"FieldDecl":"TypeDecl", name(),
//				(m_ctxt)?m_ctxt->getObjectType():-1);
		Model::global()->pop_scope(this);
}

} /* namespace psi */
