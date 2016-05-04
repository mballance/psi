/*
 * Output.h
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_
#include <string>
#include <stdio.h>

#include "classlib/Type.h"

namespace psi {

// TODO: may need an OutputBase class to enable binding
template <class T> class Output : public T {

	public:
		Output(const std::string &name, Type *p, T &t_ref) : T(name, p) {
			static_cast<Type *>(this)->setIsOutput(true);
			static_cast<Type *>(this)->setTypeData(&t_ref);
		}

		Output(const std::string &name, Type *p, const std::string &t_ref) : T(name, p) {
			static_cast<Type *>(this)->setIsOutput(true);
			static_cast<Type *>(this)->setTypeName(t_ref);
		}

		virtual ~Output() { }
};

} /* namespace psi */

#endif /* OUTPUT_H_ */
