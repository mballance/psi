/*
 * MethodParamList.h
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
 *
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_METHOD_PARAM_LIST_H
#define INCLUDED_METHOD_PARAM_LIST_H
#include <vector>
#include "classlib/pss_types.h"
#include "classlib/FieldItem.h"

namespace pss {

class MethodParamListImp;
class MethodParamList {
	friend class MethodParamListImp;
	public:

		MethodParamList();

		MethodParamList(const MethodParamList &rhs);

#ifdef PSS_HAVE_CXX_11

		MethodParamList(std::initializer_list<FieldItem> l) : MethodParamList() {
			MethodParamList &el = *this;

			for (std::initializer_list<FieldItem>::const_iterator it=l.begin();
					it!=l.end(); it++) {
				el = (el, *it);
			}
		}

		template<typename T, typename... R> static MethodParamList mklist(
				const T 			&item,
				const R&... 		rest) {
			MethodParamList plist;
			return _mklist(plist, item, rest...);
		}
#endif

		MethodParamList(const FieldItem &rhs);

		virtual ~MethodParamList();

		MethodParamList operator,(const FieldItem &rhs);
//		MethodParamList &operator,(const MethodParamList &rhs);

		MethodParamListImp *imp() const;

	private:

#ifdef PSS_HAVE_CXX_11
		template <typename T, typename... R> static MethodParamList &_mklist(
				MethodParamList		&plist,
				const T				&item,
				const R&...			rest) {
			plist = (plist, item);

			return _mklist(plist, rest...);
		}

		static MethodParamList &_mklist(MethodParamList	&plist) {
			return plist;
		}
#endif


	private:
		MethodParamListImp				*m_imp;


};

} /* namespace pss */

#endif /* SRC_PSI_CLASSLIB_EXPRLIST_H_ */
