/*
 * Scope.cpp
 *
 *  Created on: Jul 7, 2016
 *      Author: ballance
 */

#include "ModelImp.h"
#include "ScopeImp.h"

namespace psi {

Scope::Scope(bool in_field_decl) {
	m_impl = new ScopeImp(this, &typeid(this), 0, in_field_decl, "");

	m_impl->enter();
}

ScopeImp::ScopeImp(
		Scope					*master,
		const std::type_info	*type,
		BaseItemImp				*ctxt,
		bool					in_field_decl,
		const std::string		&name) :
	m_master(master), m_type(type), m_ctxt(ctxt),
	m_in_field_decl(in_field_decl), m_name(name) { }
//	m_impl->enter();
//}

Scope::Scope(const char *name) {
	m_impl = new ScopeImp(this, 0, 0, true, name);
}

Scope::Scope(const std::string &name) {
	m_impl = new ScopeImp(this, 0, 0, true, name);
}

Scope::~Scope() {
	delete m_impl;
}

ScopeImp::~ScopeImp() {

}

BaseItemImp *ScopeImp::parent() const {
	const std::vector<const ScopeImp *> &scope = ModelImp::global()->get_scope();

	// Return the first case where m_parent != this
	for (int i=scope.size()-1; i>=0; i--) {
		if (scope.at(i)->m_ctxt != m_ctxt) {
			return scope.at(i)->m_ctxt;
		}
	}

	return ModelImp::global();
}

const char *ScopeImp::name() const {
	return m_type->name();
}

void Scope::init(const std::type_info *type, BaseItem *ctxt) {
	m_impl = new ScopeImp(this, type, ctxt->impl(),
			ModelImp::global()->in_field_decl(), "");

	m_impl->enter();
}

void ScopeImp::enter() {
//		fprintf(stdout, "--> enter %s %s %d\n",
//				(m_in_field_decl)?"FieldDecl":"TypeDecl", name(),
//				(m_ctxt)?m_ctxt->getObjectType():-1);
		ModelImp::global()->push_scope(this);
}

void ScopeImp::leave() {
//		fprintf(stdout, "<-- leave %s %s %d\n",
//				(m_in_field_decl)?"FieldDecl":"TypeDecl", name(),
//				(m_ctxt)?m_ctxt->getObjectType():-1);
		ModelImp::global()->pop_scope(this);
}

} /* namespace psi */
