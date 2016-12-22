/*
 * bind.h
 *
 * Copyright 2016 Mentor Graphics Corporation
 * All Rights Reserved Worldwide
 *
 * Licensed under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in
 *  compliance with the License.  You may obtain a copy of
 *  the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in
 * writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.  See
 * the License for the specific language governing
 * permissions and limitations under the License.
 * 
 *  Created on: May 10, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_BIND_H
#define INCLUDED_BIND_H
#include <vector>
#include <functional>
#include "classlib/base_item.h"
#include "classlib/attr_item.h"
#include "classlib/pss_types.h"

namespace pss {

class bind: public base_item {
public:
	bind(base_item *p, const std::vector<attr_item *> &items);

#ifdef PSS_HAVE_CXX_11
	template<typename... I> bind(base_item *p, const I&... items)
			: bind(p, mklist(items...)) { }

	template <typename T, typename... R> static std::vector<attr_item *> mklist(
			const T &i1, const R&... rest) {
		std::vector<attr_item *> items;
		const attr_item &bi = i1;
		items.push_back(const_cast<attr_item *>(&bi));
		_mklist(items, rest...);
		return items;
	}

	template <typename T, typename... R> static void _mklist(
			std::vector<attr_item *> &items,
			const T 				 &it,
			const R&...				 rest) {
		const attr_item &bi = it;
		items.push_back(const_cast<attr_item *>(&bi));
		_mklist(items, rest...);
	}

	static void _mklist(std::vector<attr_item *> &items) { }
#endif /* PSS_HAVE_CXX_11 */

	virtual ~bind();

protected:


};

} /* namespace pss */

#endif /* INCLUDED_BIND_H */
