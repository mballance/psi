/*
 * test_main.cpp
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
 *  Created on: May 2, 2016
 *      Author: ballance
 */
#include <vector>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "pss_tests.h"
#include "classlib_impl/ModelImp.h"
#include "api_impl/ModelImpl.h"
#include "apps/PSI2XML.h"
#include "apps/XML2PSI.h"
#include "apps/PSI2PSS.h"
#include "apps/PSSXmlValidator.h"
#include "classlib_impl/Elaborator.h"
#include "TestCallbackContextImpl.h"

using namespace psi::apps;
using namespace psi;

void build_model(IModel *) __attribute__((weak));

void exec_model(IModel *) __attribute__((weak));

/**
 * Default version of the build_model function that uses
 * definitions made by the class library
 */
void build_model(IModel *model) {
	Elaborator elab;
	const char *log_level_s = getenv("PSS_LOG_LEVEL");
	Elaborator::LogLevel l = Elaborator::OFF;

	if (log_level_s) {
		if (!strcasecmp(log_level_s, "low")) {
			l = Elaborator::LOW;
		} else if (!strcasecmp(log_level_s, "med")) {
			l = Elaborator::MED;
		} else if (!strcasecmp(log_level_s, "high")) {
			l = Elaborator::HIGH;
		} else {
			fprintf(stdout, "WARNING: Unknown log level \"%s\". low, med, high supported\n",
					log_level_s);
		}
	}

	BaseItemImp *global = ModelImp::global();
	elab.set_log_level(l);
	elab.elaborate(ModelImp::global(), model);
}

void exec_model(IModel *model) {
	// Do nothing
}

int main(int argc, char **argv) {
	ModelImpl  					model;
	TestCallbackContextImpl		callback_ctxt;
	ModelImpl  					xml_model;
	PSI2XML    					psi2xml;
	XML2PSI    					xml2psi;
	PSI2PSS    					psi2pss;
	PSSXmlValidator				xml_validator;

	// We're in test mode, so don't print actual addresses
	psi2xml.setUseFixedInlineAddr();

//	std::vector<IType *>::const_iterator it;

//	fprintf(stdout, "Vector size: %d\n", global->getChildren().size());
//	for (it=global->getChildren().begin();
//			it != global->getChildren().end(); ++it) {
//		base_item *t = (*it);
//		fprintf(stdout, "PTR: %p\n", t);
//		if (t != nullptr) {
//		fprintf(stdout, "base_item: %s %s\n",
//				base_item::toString(t->getObjectType()),
//				t->getName().c_str());
//		}
//	}

	fprintf(stdout, "--> build_model\n");
	build_model(&model);
	fprintf(stdout, "<-- build_model\n");

	fprintf(stdout, "--> psi2xml\n");
	const std::string xml1 = psi2xml.traverse(&model);
	fprintf(stdout, "<-- psi2xml\n");

	fprintf(stdout, "Result:\n%s\n", xml1.c_str());

	fprintf(stdout, "--> pss_xml_validate\n");
	if (xml_validator.validate(xml1)) {
		fprintf(stdout, "XML validation succeeded\n");
	} else {
		fprintf(stdout, "XML validation failed\n");
	}
	fprintf(stdout, "<-- pss_xml_validate\n");


//	fprintf(stdout, "--> psi2pss\n");
//	const std::string pss = psi2pss.process(&model);
//	fprintf(stdout, "<-- psi2pss\n");
//
//	fprintf(stdout, "PSS Result:\n%s\n", pss.c_str());

//	fprintf(stdout, "--> xml2psi\n");
//	xml2psi.process(xml1, &xml_model);
//	fprintf(stdout, "<-- xml2psi\n");

//	const std::string xml2 = psi2xml.traverse(&xml_model);
//
//	fprintf(stdout, "Result2:\n%s\n", xml2.c_str());
//
	FILE *model_xml = fopen("model.xml", "w");
	fputs(xml1.c_str(), model_xml);
	fclose(model_xml);

//	FILE *model2_xml = fopen("model2.xml", "w");
//	fputs(xml2.c_str(), model2_xml);
//	fclose(model2_xml);

	/****************************************************************
	 * Execute model
	 ****************************************************************/
	model.setCallbackContext(&callback_ctxt);
	exec_model(&model);

	return 0;
}



