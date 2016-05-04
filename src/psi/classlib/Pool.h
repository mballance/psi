/*
 * Pool.h
 *
 *  Created on: Apr 28, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_POOL_H_
#define SRC_STATIC_POOL_H_
#include "classlib/Type.h"

namespace psi {

template <class T> class Pool : public T {

	public:
		Pool(const std::string &name, Type *p, T &t_ref) : T(name, p) {
			static_cast<Type *>(this)->setTypeData(&t_ref);
		}

		Pool(const std::string &name, Type *p, const std::string &t_ref) : T(name, p) {
			static_cast<Type *>(this)->setTypeName(t_ref);
		}

		virtual ~Pool();
};

} /* namespace psi */

#endif /* SRC_STATIC_POOL_H_ */
