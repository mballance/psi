/*
 * Lock.h
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef LOCK_H_
#define LOCK_H_
#include <string>
#include "IConstructorContext.h"

namespace psi {

template <class T> class Lock: public T {

	public:
		Lock(const std::string &name, IConstructorContext *p, T &t_ref) : T(name, p) {
			static_cast<Type *>(this)->setTypeData(&t_ref);
		}

		Lock(const std::string &name, IConstructorContext *p, const std::string &t_name) : T(name, p) {
		}

		virtual ~Lock() { }
};

} /* namespace psi */

#endif /* LOCK_H_ */
