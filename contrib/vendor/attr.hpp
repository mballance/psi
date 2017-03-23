/*
 * attr.hpp
 *
 *  Created on: Mar 23, 2017
 *      Author: ballance
 */

#ifndef CONTRIB_VENDOR_ATTR_HPP_
#define CONTRIB_VENDOR_ATTR_HPP_
#ifndef INCLUDED_ATTR_H
#include "attr.h"
#endif

namespace pss {

	template <class T> attr::attr(const scope &name) : attr_base<T>(attr_item_impl::AttrNone, name) {

	}

	template <class T> attr::~attr() {

	}

	attr<pss_int>::attr(const scope &name) : vendor::attr_item_impl(
			this, vendor::attr_item_impl::AttrNone, pss_int(), 0) {
	}

	attr<pss_int>::attr(const scope &name, const pss_int &t_decl) : vendor::attr_item_impl(
			this, vendor::attr_item_impl::AttrNone, t_decl, 0) {
	}

	void attr<pss_int>::set(int64_t v) {
		set_int(v);
	}

	int64_t attr<pss_int>::get() {
		return get_int();
	}

}




#endif /* CONTRIB_VENDOR_ATTR_HPP_ */
