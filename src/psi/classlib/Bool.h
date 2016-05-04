/*
 * Bool.h
 *
 *  Created on: Apr 28, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_BOOL_H_
#define SRC_STATIC_BOOL_H_

#include <string>

#include "classlib/Type.h"

namespace psi {

class Bool: public Type {

	public:
		Bool(const std::string &name, Type *p);

		virtual ~Bool();

};

} /* namespace psi */

#endif /* SRC_STATIC_BOOL_H_ */
