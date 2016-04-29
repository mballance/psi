/*
 * Action.h
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef ACTION_H_
#define ACTION_H_
#include <string>
#include "IConstructorContext.h"
#include "Struct.h"

namespace psi {

class Action : public Struct {

	public:

		Action(const std::string &name, IConstructorContext *p);

		virtual ~Action();

		virtual IObjectType::ObjectType getObjectType();

};

} /* namespace psi */

#endif /* ACTION_H_ */
