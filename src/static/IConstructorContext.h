/*
 * IConstructorContext.h
 *
 *  Created on: Apr 25, 2016
 *      Author: ballance
 */

#ifndef ICONSTRUCTORCONTEXT_H_
#define ICONSTRUCTORCONTEXT_H_
#include "Types.h"
#include "IObjectType.h"
#include "IDeclarationScope.h"

namespace psi {

	class IConstructorContext : public virtual IObjectType, public virtual IDeclarationScope {
		public:

			enum ConstructorContextType {
				ConstructorContext_TypeElab,
				Global,
				Package,
				Type
			};
		public:

			virtual ~IConstructorContext() { }

			virtual ConstructorContextType getContextType() = 0;

			virtual IConstructorContext *getParent() = 0;

	};
}




#endif /* ICONSTRUCTORCONTEXT_H_ */
