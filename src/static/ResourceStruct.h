/*
 * ResourceStruct.h
 *
 *  Created on: Apr 23, 2016
 *      Author: ballance
 */

#ifndef RESOURCESTRUCT_H_
#define RESOURCESTRUCT_H_
#include <string>

#include "Struct.h"
#include "Bit.h"
#include "Rand.h"

namespace psi {

class ResourceStruct : public Struct {

	public:
		Rand<psi::Bit<31,0> >			instance_id;

	public:

		ResourceStruct(
				const std::string 	&name,
				Type 				*p,
				Struct 				&super_type=Struct::None);

		ResourceStruct(
				const std::string 	&name,
				Type 				*p,
				const std::string	&super_type);

		virtual ~ResourceStruct();
};

} /* namespace psi */

#endif /* RESOURCESTRUCT_H_ */
