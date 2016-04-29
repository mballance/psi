/*
 * Extend.cpp
 *
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#include "Extend.h"

namespace psi {

Extend::Extend(IConstructorContext *p, ExtendType t) :
		m_parent(p), m_type(t) {

	// Add this extension to the accumulating list
	p->add(this);

}

Extend::~Extend() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
