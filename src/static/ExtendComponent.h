/*
 * ExtendComponent.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_EXTENDCOMPONENT_H_
#define SRC_STATIC_EXTENDCOMPONENT_H_
#include "Type.h"

namespace psi {

template <class T> class ExtendComponent : public T {

	public:
		ExtendComponent(Type *p, T &t_ref) : T("<Extension>", p) {
			Type *t = static_cast<Type *>(this);
			t->setTypeData(&t_ref);
			t->setObjectType(Type::TypeExtendComponent);
		}

		virtual ~ExtendComponent() { }

};

} /* namespace psi */

#endif /* SRC_STATIC_EXTENDCOMPONENT_H_ */
