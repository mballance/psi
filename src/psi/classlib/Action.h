/*
 * Action.h
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef ACTION_H_
#define ACTION_H_
#include <string>

#include "classlib/Exec.h"
#include "classlib/Type.h"

namespace psi {

class Action : public Type {

	public:

		Action(const std::string &name, Type *p);

		virtual ~Action();

//		virtual Graph graph();

};

} /* namespace psi */

#endif /* ACTION_H_ */
