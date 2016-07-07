/*
 * Scope.cpp
 *
 *  Created on: Jul 7, 2016
 *      Author: ballance
 */

#include "classlib/Scope.h"
#include "classlib/Model.h"

namespace psi {

Scope::Scope(int v) {
	m_type = &typeid(this);
	m_ctxt = Model::global();
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
	if (!m_ctxt) {
		m_ctxt = Model::global();
	}
	Model::global()->push_scope(this);
}

void Scope::leave() {
	Model::global()->pop_scope();
}

} /* namespace psi */
