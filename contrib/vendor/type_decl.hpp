/*
 * type_decl.hpp
 *
 *  Created on: Mar 21, 2017
 *      Author: ballance
 */

#ifndef CONTRIB_VENDOR_TYPE_DECL_HPP_
#define CONTRIB_VENDOR_TYPE_DECL_HPP_

#ifndef INCLUDED_TYPE_DECL_H
#include "type_decl.h"
#endif

namespace pss {

template <class T> type_decl::type_decl() : vendor::type_decl_impl<T>() {

}

template <class T> T *type_decl::id() {
	return vendor::type_decl_impl<T>::id();
}

}




#endif /* CONTRIB_VENDOR_TYPE_DECL_HPP_ */
