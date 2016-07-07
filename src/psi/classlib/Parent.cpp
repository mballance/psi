/*
 * Parent.cpp
 *
 *  Created on: Jul 7, 2016
 *      Author: ballance
 */

#include "classlib/Parent.h"
#include "classlib/Model.h"

namespace psi {

Parent::Parent(int v) {
	m_type = &typeid(this);
	m_ctxt = Model::global();
	enter();
}

Parent::~Parent() {
	leave();
}

Type *Parent::parent() const {
	const std::vector<const Parent *> &scope = Model::global()->get_scope();

	// Return the first case where m_parent != this
	for (int i=scope.size()-1; i>=0; i--) {
		if (scope.at(i)->m_ctxt != m_ctxt) {
			return scope.at(i)->m_ctxt;
		}
	}

	fprintf(stdout, "Error: Fell off the end of Parent::parent\n");

	return Model::global();
}

const char *Parent::name() const {
	return m_type->name();
}

void Parent::enter() {
	if (!m_ctxt) {
		m_ctxt = Model::global();
	}
	Model::global()->push_scope(this);
}

void Parent::leave() {
	Model::global()->pop_scope();
}

} /* namespace psi */
