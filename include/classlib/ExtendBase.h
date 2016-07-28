/*
 * ExtendBase.h
 *
 *  Created on: Jul 27, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_EXTEND_BASE_H
#define INCLUDED_EXTEND_BASE_H

#include "classlib/ExtendItem.h"

namespace psi {

template <class T> class ExtendBase : public T {
public:

	ExtendBase(BaseItem *p) : m_item(p) {
		m_item.setDataType(TypeDecl<T>::type_id());
	}

private:
	ExtendItem					m_item;

};

}




#endif /* INCLUDE_CLASSLIB_EXTENDBASE_H_ */
