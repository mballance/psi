/*
 * AttributesImpl.h
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
 *  Created on: Aug 16, 2016
 *      Author: ballance
 */

#ifndef CONTRIB_API_IMPL_ATTRIBUTESIMPL_H_
#define CONTRIB_API_IMPL_ATTRIBUTESIMPL_H_
#include "api/IAttributes.h"
#include <map>
#include <string>

using namespace psi_api;

namespace psi {

class AttributesImpl: public virtual IAttributes {
public:
	AttributesImpl();

	virtual ~AttributesImpl();

	virtual const std::string &getAttribute(const std::string &key);

	virtual void getAttributes(std::vector<std::string> &keys);

	virtual bool hasAttribute(const std::string &key);

	virtual void setAttribute(const std::string &key, const std::string &val);

	virtual void clearAttribute(const std::string &key);

private:
	std::map<std::string,std::string>	m_attr;
	static std::string					m_null_attr;


};

} /* namespace psi */

#endif /* CONTRIB_API_IMPL_ATTRIBUTESIMPL_H_ */
