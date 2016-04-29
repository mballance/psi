/*
 * IDeclarationScope.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_IDECLARATIONSCOPE_H_
#define SRC_STATIC_IDECLARATIONSCOPE_H_
#include "Types.h"

namespace psi {

	class Action;
	class Component;
	class Package;
	class Type;
	class Extend;

	class IDeclarationScope {

		public:

			virtual ~IDeclarationScope() { }

			virtual void add(Action *action) = 0;

			virtual void add(Component *component) = 0;

			virtual void add(Package *package) = 0;

			virtual void add(Extend *extend) = 0;

			virtual void addField(Type *t) = 0;

	};
}




#endif /* SRC_STATIC_IDECLARATIONSCOPE_H_ */
