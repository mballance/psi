/*
 * BindPathImpl.h
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
 *  Created on: Jul 22, 2016
 *      Author: ballance
 */

#ifndef IMPL_BINDPATHIMPL_H_
#define IMPL_BINDPATHIMPL_H_
#include "api/IBindPath.h"

using namespace psi_api;

namespace psi {

class BindPathImpl: public IBindPath {
public:
	BindPathImpl(const std::vector<IBaseItem *> &path);

	virtual ~BindPathImpl();

	virtual const std::vector<IBaseItem *> &getPath() const { return m_path; }

private:
	std::vector<IBaseItem *>			m_path;

};

} /* namespace psi */

#endif /* IMPL_BINDPATHIMPL_H_ */
