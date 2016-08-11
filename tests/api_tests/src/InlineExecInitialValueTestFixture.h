/*
 * InlineExecInitialValueTestFixture.h
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
