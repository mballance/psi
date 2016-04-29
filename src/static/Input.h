/*
 * Input.h
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef INPUT_H_
#define INPUT_H_
#include <string>
#include "IConstructorContext.h"
#include "Type.h"

namespace psi {

template <class T> class Input : public T {

	public:
		Input(const std::string &name, IConstructorContext *p, T &t_ref) : T(name, p) {
			static_cast<Type *>(this)->setIsInput(true);
			static_cast<Type *>(this)->setTypeData(&t_ref);
		}

		virtual ~Input() { }
};

} /* namespace psi */

#endif /* INPUT_H_ */
