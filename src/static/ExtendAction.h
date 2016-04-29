/*
 * ExtendAction.h
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef SRC_STATIC_EXTENDACTION_H_
#define SRC_STATIC_EXTENDACTION_H_
#include "Extend.h"

namespace psi {

template <class T> class ExtendAction : public T {

	public:
		ExtendAction(IConstructorContext *p, T &t_ref) : T("<Unknown>", p) {
		}

		virtual ~ExtendAction() { }

};

} /* namespace psi */

#endif /* SRC_STATIC_EXTENDACTION_H_ */
