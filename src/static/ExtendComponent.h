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

template <class T> class ExtendComponent : public Extend {

	public:
		ExtendComponent(IConstructorContext *p, T &t_ref) : Extend(p, Extend::Component) {
		}

		virtual ~ExtendComponent() { }

};

} /* namespace psi */

#endif /* SRC_STATIC_EXTENDCOMPONENT_H_ */
