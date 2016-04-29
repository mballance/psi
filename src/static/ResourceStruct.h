/*
 * ResourceStruct.h
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef RESOURCESTRUCT_H_
#define RESOURCESTRUCT_H_
#include <string>
#include "IConstructorContext.h"
#include "Struct.h"
#include "Bit.h"
#include "Rand.h"

namespace psi {

class ResourceStruct : public Struct {

	public:
		Rand<Bit<31,0> >			instance_id;

	public:
		ResourceStruct(const std::string &name, IConstructorContext *p);

		virtual ~ResourceStruct();
};

} /* namespace psi */

#endif /* RESOURCESTRUCT_H_ */
