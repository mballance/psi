/*
 * Share.h
 *
 *  Created on: Apr 28, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_SHARE_H_
#define SRC_STATIC_SHARE_H_
#include "classlib/Type.h"

namespace psi {

template <class T> class Share : public T {
	public:

		Share(const std::string &name, Type *p, T &t_ref) : T(name, p) {
			static_cast<Type *>(this)->setTypeData(&t_ref);
		}

		Share(const std::string &name, Type *p, const std::string &t_ref) : T(name, p) {
			static_cast<Type *>(this)->setTypeName(t_ref);
		}

		virtual ~Share();
};

} /* namespace psi */

#endif /* SRC_STATIC_SHARE_H_ */
