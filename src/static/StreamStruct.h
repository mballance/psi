/*
 * StreamStruct.h
 *
 *  Created on: Apr 28, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_STREAMSTRUCT_H_
#define SRC_STATIC_STREAMSTRUCT_H_
#include "Struct.h"

namespace psi {

class StreamStruct : public Struct {

	public:

		StreamStruct(
				const std::string 	&name,
				Type 				*p,
				Struct				&super_type=Struct::None);

		StreamStruct(
				const std::string 	&name,
				Type 				*p,
				const std::string	&super_type);

		virtual ~StreamStruct();
};

} /* namespace psi */

#endif /* SRC_STATIC_STREAMSTRUCT_H_ */
