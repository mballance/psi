/*
 * Extend.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_EXTEND_H_
#define SRC_STATIC_EXTEND_H_
#include "DeclarationScope.h"
#include "IConstructorContext.h"

namespace psi {

class Extend : public DeclarationScope, public virtual IConstructorContext {

	public:

		enum ExtendType {
			Action,
			Struct,
			Component
		};


	public:

		Extend(IConstructorContext *p, ExtendType t);

		virtual ~Extend();

		virtual IObjectType::ObjectType getObjectType() {
			return IObjectType::Extend;
		}

		virtual IConstructorContext::ConstructorContextType getContextType() {
			return IConstructorContext::Global;
		}

		virtual IConstructorContext *getParent() {
			return m_parent;
		}

	private:

		IConstructorContext			*m_parent;
		ExtendType					m_type;

};

} /* namespace psi */

#endif /* SRC_STATIC_EXTEND_H_ */
