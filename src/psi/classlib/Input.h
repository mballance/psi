/*
 * Input.h
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef INPUT_H_
#define INPUT_H_
#include <string>

#include "classlib/Type.h"

namespace psi {

template <class T> class Input : public T {

	public:
		Input(const std::string &name, Type *p, T &t_ref) : T(name, p) {
			static_cast<Type *>(this)->setIsInput(true);
			static_cast<Type *>(this)->setTypeData(&t_ref);
		}

		Input(const std::string &name, Type *p, const std::string &t_ref) : T(name, p) {
			static_cast<Type *>(this)->setIsInput(true);
			static_cast<Type *>(this)->setTypeData(nullptr);
			static_cast<Type *>(this)->setTypeName(t_ref);
		}

		virtual ~Input() { }
};

} /* namespace psi */

#endif /* INPUT_H_ */
