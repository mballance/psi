/*
 * Component.h
 *
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_
#include <string>

#include "Type.h"

namespace psi {

class Component : public Type {

	public:
		Component(const std::string &name, Type *p);

		virtual ~Component();

};

} /* namespace psi */

#endif /* COMPONENT_H_ */
