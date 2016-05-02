/*
 * ExtendAction.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_EXTENDACTION_H_
#define SRC_STATIC_EXTENDACTION_H_
#include "Type.h"

namespace psi {

template <class T> class ExtendAction : public T {

	public:
		ExtendAction(Type *p, T &t_ref) : T("<Extension>", p) {
			Type *t = static_cast<Type *>(this);
			t->setTypeData(&t_ref);
			t->setObjectType(Type::TypeExtendAction);
		}

		virtual ~ExtendAction() { }

};

} /* namespace psi */

#endif /* SRC_STATIC_EXTENDACTION_H_ */
