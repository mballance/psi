/*
 * PSIFileUtils.cpp
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
 *  Created on: Sep 13, 2016
 *      Author: ballance
 */

#include "PSIFileUtils.h"

namespace psi {

PSIFileUtils::PSIFileUtils() {
	// TODO Auto-generated constructor stub

}

PSIFileUtils::~PSIFileUtils() {
	// TODO Auto-generated destructor stub
}

std::string PSIFileUtils::read(FILE *fp) {
	char tmp[1024];
	size_t sz;
	std::string ret;

	while ((sz = fread(tmp, 1, sizeof(tmp), fp)) > 0) {
		for (uint32_t i=0; i<sz; i++) {
			ret.push_back(tmp[i]);
		}
	}

	return ret;
}

std::string PSIFileUtils::expand(const std::string &str) {
	std::string ret;
	std::string var;
	const char *val;
	uint32_t i=0;
	char c;

	while (i < str.length()) {
		if (str.at(i) == '$') {
			bool expect_closebrace=false;

			var="";
			i++;
			if (str.at(i) == '{') {
				i++;
			}

			while (!isspace((c=str.at(i))) &&
					(isalnum(c) || c == '_')) {
				var.push_back(str.at(i));
				i++;
			}

			if (str.at(i) == '}') {
				i++;
			}

			val = getenv(var.c_str());

			if (val) {
				ret.append(val);
			}
		} else {
			ret.push_back(str.at(i));
			i++;
		}
	}

	return ret;
}

} /* namespace psi */
