/*
 * PSSXmlValidator.h
 *
 *  Created on: Jul 19, 2016
 *      Author: ballance
 */

#ifndef SRC_APPS_PSSXMLVALIDATOR_H_
#define SRC_APPS_PSSXMLVALIDATOR_H_
#include <libxml2/libxml/xmlschemastypes.h>
#include <string>

namespace psi {

class PSSXmlValidator {
public:
	PSSXmlValidator();

	virtual ~PSSXmlValidator();

	bool validate(
			const std::string &content,
			const std::string &name="unnamed.xml");

private:
	xmlSchemaPtr				m_schema;
};

} /* namespace psi */

#endif /* SRC_APPS_PSSXMLVALIDATOR_H_ */
