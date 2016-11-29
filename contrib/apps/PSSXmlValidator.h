/*
 * PSSXmlValidator.h
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
