/*
 * Package.h
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef PACKAGE_H_
#define PACKAGE_H_

#include <string>

#include "classlib/Type.h"

namespace psi {

class Package : public Type {

	public:

		Package(const std::string &name, Type *p=nullptr);

		virtual ~Package();

};

} /* namespace psi */

#endif /* PACKAGE_H_ */
