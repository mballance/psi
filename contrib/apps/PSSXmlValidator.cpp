/*
 * PSSXmlValidator.cpp
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
 *  Created on: Jul 19, 2016
 *      Author: ballance
 */

#include "PSSXmlValidator.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Schema string
extern const char *PSSModel;

namespace psi {

PSSXmlValidator::PSSXmlValidator() : m_schema(0) {

}

PSSXmlValidator::~PSSXmlValidator() {
	if (m_schema) {
		xmlSchemaFree(m_schema);
	}
}

bool PSSXmlValidator::validate(
		const std::string &content,
		const std::string &name) {
	if (!m_schema) {
		xmlSchemaParserCtxtPtr ctxt = xmlSchemaNewMemParserCtxt(PSSModel, strlen(PSSModel));
		xmlSchemaSetParserErrors(ctxt, (xmlSchemaValidityErrorFunc)fprintf,
				(xmlSchemaValidityWarningFunc)fprintf, stdout);
		m_schema = xmlSchemaParse(ctxt);
		xmlSchemaFreeParserCtxt(ctxt);
	}

	xmlDocPtr doc = xmlReadMemory(
			content.c_str(),
			(int)content.size(),
			name.c_str(), 0, 0);

	if (!doc) {
		fprintf(stdout, "Error: Failed to read XML document %s\n", name.c_str());
		return false;
	}

	xmlSchemaValidCtxtPtr ctxt = xmlSchemaNewValidCtxt(m_schema);

	xmlSchemaSetValidErrors(ctxt, (xmlSchemaValidityErrorFunc)fprintf,
			(xmlSchemaValidityWarningFunc)fprintf, stdout);

	int ret = xmlSchemaValidateDoc(ctxt, doc);

	xmlSchemaFreeValidCtxt(ctxt);
	xmlFreeDoc(doc);

	return (ret == 0);
}


} /* namespace psi */
