/*
 * BaseItemImpl.h
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
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef IMPL_BASEITEMIMPL_H_
#define IMPL_BASEITEMIMPL_H_
#include <map>
#include <string>
#include "api/IBaseItem.h"
#include "AttributesImpl.h"

#ifndef PSS_HAVE_CXX_11
#if __cplusplus >= 201103L
#define PSS_HAVE_CXX_11
#endif
#endif

#ifdef PSS_HAVE_CXX_11
#include <initializer_list>
#include <type_traits>
#endif

using namespace psi_api;

namespace psi {

	class BaseItemImpl :
			public virtual IBaseItem,
			public virtual AttributesImpl {
		public:

			BaseItemImpl(IBaseItem::ItemType t);

			virtual ~BaseItemImpl();

			virtual IBaseItem::ItemType getType() const;

			virtual void setType(IBaseItem::ItemType t);

			virtual IBaseItem *getParent() const { return m_parent; }

			virtual void setParent(IBaseItem *p) { m_parent = p; }

		private:
			IBaseItem::ItemType					m_type;
			IBaseItem							*m_parent;
};

} /* namespace psi */

#endif /* IMPL_BASEITEMIMPL_H_ */
