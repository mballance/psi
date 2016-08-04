/*
 * TypePathImp.h
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

#ifndef INCLUDED_TYPE_PATH_IMPL_H
#define INCLUDED_TYPE_PATH_IMPL_H
#include <string>
#include <vector>

namespace pss {

class TypePathImp {
public:

	TypePathImp();

	TypePathImp(const std::string &path);

	TypePathImp(const std::vector<std::string> &path);

	virtual ~TypePathImp();

	bool isNull() const { return m_path.size() == 0; }

	const std::vector<std::string> &get() const { return m_path; }

	void set(const std::vector<std::string> &path);

	const std::string &leaf() const;

	void prepend(const std::string &elem) { m_path.insert(m_path.begin(), elem); }

	void append(const std::string &elem) { m_path.push_back(elem); }

	std::string toString() const;

private:
	std::vector<std::string>		m_path;
	std::string						m_null;

};

} /* namespace pss */

#endif /* SRC_PSI_CLASSLIB_TYPEPATH_H_ */
