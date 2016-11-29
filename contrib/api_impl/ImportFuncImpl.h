/*
 * ImportFuncImpl.h
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
 *  Created on: Aug 11, 2016
 *      Author: ballance
 */

#ifndef CONTRIB_API_IMPL_IMPORTFUNCIMPL_H_
#define CONTRIB_API_IMPL_IMPORTFUNCIMPL_H_
#include <string>
#include <vector>
#include "BaseItemImpl.h"
#include "NamedItemImpl.h"
#include "api/IImportFunc.h"
#include "api/IField.h"

namespace psi {

class ImportFuncImpl : public IImportFunc,
	public virtual BaseItemImpl,
	public virtual NamedItemImpl {
public:
	ImportFuncImpl(
			const std::string				&name,
			IBaseItem						*ret_type,
			const std::vector<IField *>		&parameters);

	virtual ~ImportFuncImpl();

	IBaseItem *getReturnType() const { return m_ret; }

	const std::vector<IField *> &getParameters() const {
		return m_parameters;
	}


private:
	IBaseItem					*m_ret;
	std::vector<IField *>		m_parameters;
};

} /* namespace psi_api */

#endif /* CONTRIB_API_IMPL_IMPORTFUNCIMPL_H_ */
