/*
 * DeclarationScope.cpp
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#include "DeclarationScope.h"
#include "Type.h"
#include "Action.h"
#include "Component.h"
#include "Extend.h"
#include <stdio.h>

namespace psi {

DeclarationScope::DeclarationScope() {
	// TODO Auto-generated constructor stub

}

DeclarationScope::~DeclarationScope() {
	// TODO Auto-generated destructor stub
}

void DeclarationScope::add(Package *p) {
	m_packages.push_back(p);
}

void DeclarationScope::add(Action *a) {
	m_actions.push_back(a);
}

void DeclarationScope::add(Component *c) {
	m_components.push_back(c);
}

void DeclarationScope::add(Extend *e) {
	m_extensions.push_back(e);
}

void DeclarationScope::addField(Type *t) {
	fprintf(stdout, "addField: %p %s isRand=%s isInput=%s isOutput=%s\n",
			t, t->getName().c_str(),
			(t->isRand())?"true":"false",
			(t->isInput())?"true":"false",
			(t->isOutput())?"true":"false"
					);
	m_fields.push_back(t);
}

void DeclarationScope::build() {
	std::vector<Action *>::const_iterator it;
	std::vector<Component *>::iterator c_it;
	std::vector<Type *>::const_iterator f_it;

	fprintf(stdout, "build\n");

	for (c_it=m_components.begin(); c_it!=m_components.end(); c_it++) {
		Component *c = *c_it;
		fprintf(stdout, "Component: %s\n", c->getName().c_str());
		for (it=c->getActions().begin(); it!=c->getActions().end(); it++) {
			Action *a = *it;
			fprintf(stdout, "    Action: %s\n", a->getName().c_str());
			for (f_it = a->getFields().begin(); f_it!=a->getFields().end(); f_it++) {
				Type *t = *f_it;
				fprintf(stdout, "        Field: %s isRand=%s\n",
						t->getName().c_str(),
						(t->isRand())?"true":"false");
				if (t->getTypeData() != nullptr) {
//					fprintf(stdout, "            Type=%s\n", t->getTypeData()->getName().c_str());
					IConstructorContext *ctxt = t->getTypeData();
//					while (ctxt != nullptr) {
//						fprintf(stdout, "            ctxt=%p\n", ctxt);
//						ctxt = ctxt->getParent();
//					}
				}
			}
		}
	}
}

const std::vector<Action *> &DeclarationScope::getActions() const {
	return m_actions;
}

const std::vector<Type *> &DeclarationScope::getFields() const {
	return m_fields;
}

} /* namespace psi */
