/*
 * Bind.h
 *
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#ifndef SRC_PSI_CLASSLIB_BIND_H_
#define SRC_PSI_CLASSLIB_BIND_H_
#include <vector>
#include <functional>
#include "Type.h"

namespace psi {

class Bind: public Type {
public:
	Bind(Type *p, Type &i1, Type &i2);

	Bind(Type *p, Type *i1, Type *i2);

	Bind(Type *p, const std::vector<Type *> &items);

	virtual ~Bind();
};

} /* namespace psi */

#endif /* SRC_PSI_CLASSLIB_BIND_H_ */
