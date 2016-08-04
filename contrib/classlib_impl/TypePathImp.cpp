/*
 * TypePathImp.cpp
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 *  Created on: Jul 13, 2016
 *      Author: ballance
 */

#include "TypePathImp.h"

namespace pss {

TypePathImp::TypePathImp() { }

TypePathImp::TypePathImp(const std::vector<std::string> &path) :
	m_path(path) { }

TypePathImp::TypePathImp(const std::string &path) {
	m_path.push_back(path);
}

void TypePathImp::set(const std::vector<std::string> &path) {
	m_path.clear();

	for (std::vector<std::string>::const_iterator it=path.begin();
			it!=path.end(); it++) {
		std::string tmp = *it;
		m_path.push_back(tmp);
	}
}

const std::string &TypePathImp::leaf() const {
	return (m_path.size()>0)?m_path.at(m_path.size()-1):m_null;
}

TypePathImp::~TypePathImp() {
	// TODO Auto-generated destructor stub
}

std::string TypePathImp::toString() const {
	std::string ret;

	if (isNull()) {
		ret.append("(Empty)");
	} else {
		for (std::vector<std::string>::const_iterator it=m_path.begin();
				it!=m_path.end(); it++) {
			if (ret.size() > 0) {
				ret.append("::");
			}
			ret.append(*it);
		}
	}

	return ret;
}

} /* namespace pss */
