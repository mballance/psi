/*
 * InlineExecInitialValueTestFixture.cpp
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

#include "InlineExecInitialValueTestFixture.h"
#include "TestCallbackContextImpl.h"
#include "InlineExecIterator.h"

InlineExecInitialValueTestFixture::InlineExecInitialValueTestFixture() {
	// TODO Auto-generated constructor stub

}

InlineExecInitialValueTestFixture::~InlineExecInitialValueTestFixture() {
	// TODO Auto-generated destructor stub
}

void InlineExecInitialValueTestFixture::run(
		IModel				*model,
		const std::string	&comp_name,
		const std::string	&action_name,
		const std::string	&initial) {
	TestCallbackContextImpl *ctxt = static_cast<TestCallbackContextImpl *>(model->getCallbackContext());
	InlineExecIterator *iterator = new InlineExecIterator(
			model, comp_name, action_name, initial);

	fprintf(stdout, "Note: initial field values:\n%s\n", initial.c_str());

	iterator->traverse();

	fprintf(stdout, "Note: final field values:\n%s\n",
			ctxt->toString().c_str());

	FILE *values = fopen("values.xml", "w");
	ctxt->setChandleTestMode(true);
	fputs(ctxt->toString().c_str(), values);
	fclose(values);

	delete iterator;
}

