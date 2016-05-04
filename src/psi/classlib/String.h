/*
 * String.h
 *
 *  Created on: Apr 28, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_STRING_H_
#define SRC_STATIC_STRING_H_
#include "classlib/Type.h"

namespace psi {

class String : public Type {

	public:

		String(const std::string &name, Type *p);

		virtual ~String();
};

} /* namespace psi */

#endif /* SRC_STATIC_STRING_H_ */
