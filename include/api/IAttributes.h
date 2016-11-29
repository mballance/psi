/*
 * IAttributes.h
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
 *  Created on: Aug 15, 2016
 *      Author: ballance
 */

#ifndef INCLUDED_IATTRIBUTES_H
#define INCLUDED_IATTRIBUTES_H
#include <string>
#include <vector>

namespace psi_api {

class IAttributes {
public:
	virtual ~IAttributes() { }

	virtual const std::string &getAttribute(const std::string &key) = 0;

	virtual void getAttributes(std::vector<std::string> &keys) = 0;

	virtual bool hasAttribute(const std::string &key) = 0;

	virtual void setAttribute(const std::string &key, const std::string &val) = 0;

	virtual void clearAttribute(const std::string &key) = 0;

};

}


#endif /* INCLUDED_IATTRIBUTES_H */
