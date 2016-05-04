/*
 * Rand.h
 *
 *  Created on: Apr 25, 2016
 *      Author: ballance
 */

#ifndef SRC_RAND_H_
#define SRC_RAND_H_
#include <string>

#include "classlib/Type.h"

namespace psi {

template <class T> class Rand : public T {

	public:
		Rand(const std::string &name, Type *p) : T(name, p) {
			Type *t = static_cast<Type *>(this);
			t->setIsRand(true);
		}

		virtual ~Rand() { };

};

} /* namespace psi */

#endif /* SRC_RAND_H_ */
