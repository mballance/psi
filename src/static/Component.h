/*
 * Component.h
 *
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_
#include <string>
#include "IConstructorContext.h"
#include "DeclarationScope.h"
#include "Type.h"
#include "TypeRegistry.h"

namespace psi {

class Component : public Type, public virtual IConstructorContext {

	public:
		Component(const std::string &name, IConstructorContext *p=TypeRegistry::global());

		virtual ~Component();

		virtual ConstructorContextType getContextType();

		virtual IObjectType::ObjectType getObjectType();

};

} /* namespace psi */

#endif /* COMPONENT_H_ */
