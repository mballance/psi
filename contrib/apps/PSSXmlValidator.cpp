/*
 * PSSXmlValidator.cpp
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
