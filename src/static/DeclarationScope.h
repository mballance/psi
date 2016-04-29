/*
 * DeclarationScope.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_DECLARATIONSCOPE_H_
#define SRC_STATIC_DECLARATIONSCOPE_H_

#include <vector>
#include "IDeclarationScope.h"

namespace psi {

class Action;
class Component;
class Package;
class Extend;

class DeclarationScope : public virtual IDeclarationScope {

	public:

		DeclarationScope();

		virtual ~DeclarationScope();

		virtual void add(Action *action);

		virtual void add(Component *component);

		virtual void add(Package *package);

		virtual void add(Extend *extends);

		virtual void addField(Type *t);

		void build();

	protected:
		const std::vector<Action *> &getActions() const;

		const std::vector<Type *> &getFields() const;

	protected:
		std::vector<Action *>				m_actions;
		std::vector<Component *>			m_components;
		std::vector<Package *>				m_packages;
		std::vector<Type *>					m_fields;
		std::vector<Extend *>				m_extensions;

};

} /* namespace psi */

#endif /* SRC_STATIC_DECLARATIONSCOPE_H_ */
