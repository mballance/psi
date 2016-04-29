/*
 * ExtendComponent.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_EXTENDCOMPONENT_H_
#define SRC_STATIC_EXTENDCOMPONENT_H_
#include "Extend.h"

namespace psi {

template <class T> class ExtendComponent : public T {

	public:
		ExtendComponent(IConstructorContext *p, T &t_ref) : T("<Extension>", m) {
			// TODO: need to pass on extension data
		}

		virtual ~ExtendComponent() { }

};

} /* namespace psi */

#endif /* SRC_STATIC_EXTENDCOMPONENT_H_ */
