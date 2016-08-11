/*
 * InlineExecInitialValueTestFixture.cpp
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

