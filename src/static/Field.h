/*
 * Field.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_FIELD_H_
#define SRC_STATIC_FIELD_H_

#include <string>

#include "Type.h"

namespace psi {

template <class T> class Field : public T {
	public:

		Field(const std::string &name, IConstructorContext *p, T &t_ref) : T(name, p) {
			Type *t = static_cast<Type *>(this);
			t->setTypeData(&t_ref);
		}
};

}




#endif /* SRC_STATIC_FIELD_H_ */
