/*
 * Package.h
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef PACKAGE_H_
#define PACKAGE_H_

#include <string>

#include "DeclarationScope.h"
#include "IConstructorContext.h"
#include "TypeRegistry.h"

namespace psi {

class Package : public DeclarationScope, public virtual IConstructorContext {

	public:

		Package(const std::string &name, IConstructorContext *p=nullptr);

		virtual ~Package();

		virtual IObjectType::ObjectType getObjectType();

		virtual IConstructorContext::ConstructorContextType getContextType() {
			// TODO: Placeholder
			return IConstructorContext::Global;
		}

		virtual IConstructorContext *getParent() {
			return TypeRegistry::global();
		}

	public:
		static ObjectType				m_object_type;
};

} /* namespace psi */

#endif /* PACKAGE_H_ */
