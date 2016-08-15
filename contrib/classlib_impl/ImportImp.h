/*
 * Import.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 *  Created on: Apr 29, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_IMPORT_IMP_H
#define INCLUDED_IMPORT_IMP_H
#include <string>

#include "classlib/Import.h"
#include "NamedBaseItemImp.h"

namespace pss {

class ImportImp : public NamedBaseItemImp {

	public:

		ImportImp(
				Import				*master,
				BaseItem 			*p,
				const std::string 	&name,
				const ExprList 		&plist);

		ImportImp(
				Import				*master,
				BaseItem 			*p,
				const std::string 	&name,
				const BaseItem 		&ret,
				const ExprList 		&plist);

		virtual ~ImportImp();

		ExprImportCall operator()(const ExprList &plist);

		ExprImportCall operator()();

		BaseItemImp *getReturnType() {
			return (m_have_ret)?&m_ret:0;
		}

		const ExprList &getParameters() const { return m_parameters; }

	private:

		bool						m_have_ret;
		BaseItemImp					m_ret;
		ExprList					m_parameters;

};


} /* namespace pss */

#endif /* SRC_CLASSLIB_IMPORT_H_ */
