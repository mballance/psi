/*
 * Struct.h
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef STRUCT_H_
#define STRUCT_H_
#include <string>
#include "IConstructorContext.h"
#include "DeclarationScope.h"
#include "Type.h"
#include "IObjectType.h"

namespace psi {

class Struct : public Type, public virtual IObjectType {

	public:

		Struct(const std::string &name, IConstructorContext *p);

		virtual ~Struct();

		virtual IObjectType::ObjectType getObjectType();

	public:
		static ObjectType				m_object_type;
		static Struct					None;
};

} /* namespace psi */

#endif /* STRUCT_H_ */
