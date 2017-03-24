/*
 * BindImpl.h
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
 *  Created on: May 23, 2016
 *      Author: ballance
 */

#ifndef IMPL_BINDIMPL_H_
#define IMPL_BINDIMPL_H_
#include <vector>

#include "../../include/api/psi_api.h"
#include "api/IBind.h"
#include "BaseItemImpl.h"

using namespace psi_api;

namespace psi {

class BindImpl: public virtual IBind, public virtual BaseItemImpl {
public:
	BindImpl(const std::vector<IBindPath *> &targets);

	virtual ~BindImpl();

	virtual const std::vector<IBindPath *> &getTargets() const { return m_targets; }

private:
	std::vector<IBindPath *>				m_targets;

};

} /* namespace psi */

#endif /* IMPL_BINDIMPL_H_ */
