/*
 * InlineExecInitialValueTestFixture.h
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
 *  Created on: Aug 10, 2016
 *      Author: ballance
 */

#ifndef TESTS_API_TESTS_SRC_INLINEEXECINITIALVALUETESTFIXTURE_H_
#define TESTS_API_TESTS_SRC_INLINEEXECINITIALVALUETESTFIXTURE_H_
#include <string>
#include "api/IModel.h"

using namespace psi_api;

class InlineExecInitialValueTestFixture {
public:
	InlineExecInitialValueTestFixture();

	virtual ~InlineExecInitialValueTestFixture();

	static void run(
			IModel 				*model,
			const std::string	&comp_name,
			const std::string	&action_name,
			const std::string	&initial);

};

#endif /* TESTS_API_TESTS_SRC_INLINEEXECINITIALVALUETESTFIXTURE_H_ */
