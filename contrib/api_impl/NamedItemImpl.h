/*
 * NamedItemImpl.h
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
 *  Created on: Apr 26, 2016
 *      Author: ballance
 */

#ifndef IMPL_NAMEDITEMIMPL_H_
#define IMPL_NAMEDITEMIMPL_H_
#include <string>

#include "BaseItemImpl.h"
#include "api/INamedItem.h"

using namespace psi_api;

namespace psi {

class NamedItemImpl : public virtual INamedItem {
	public:

		NamedItemImpl(const std::string &name);

		virtual ~NamedItemImpl();

		virtual const std::string &getName();

		virtual const std::string &getName() const;

		virtual void setName(const std::string &name);

	private:

		std::string					m_name;
};

} /* namespace psi */

#endif /* IMPL_NAMEDITEMIMPL_H_ */
