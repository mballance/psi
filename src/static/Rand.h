/*
 * Rand.h
 *
 *  Created on: Apr 25, 2016
 *      Author: ballance
 */

#ifndef SRC_RAND_H_
#define SRC_RAND_H_
#include <string>
#include "IConstructorContext.h"
#include "Type.h"

namespace psi {

template <class T> class Rand : public T {

	public:
		Rand(const std::string &name, IConstructorContext *p) : T(name, p) {
			static_cast<Type *>(this)->setIsRand(true);
		}

		virtual ~Rand() { };

};

} /* namespace psi */

#endif /* SRC_RAND_H_ */
