/*
 * ExtendStruct.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_EXTENDSTRUCT_H_
#define SRC_STATIC_EXTENDSTRUCT_H_
#include "Extend.h"

namespace psi {

template <class T> class ExtendStruct : public Extend {

	public:
		ExtendStruct(IConstructorContext *p, T &t_ref) : Extend(p, Extend::Struct) {
		}

		virtual ~ExtendStruct() { }

};

} /* namespace psi */

#endif /* SRC_STATIC_EXTENDSTRUCT_H_ */
