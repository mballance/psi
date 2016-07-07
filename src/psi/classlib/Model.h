/*
 * Model.h
 *
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
 *  Created on: Apr 25, 2016
 *      Author: ballance
 */

#ifndef SRC_TYPEREGISTRY_H_
#define SRC_TYPEREGISTRY_H_

#include <string>
#include <vector>

#include "classlib/Type.h"

namespace psi {

class Package;
class Parent;
class Model : public Type {
	friend class Package;

	public:
		Model();

		virtual ~Model();

		static Model *global();

		void push_scope(const Parent *p);

		void pop_scope();

		const std::vector<const Parent *> &get_scope() const;

	private:
		std::vector<const Parent *>		m_scope;

		static Model			*m_global;

};


} /* namespace psi */


#endif /* SRC_TYPEREGISTRY_H_ */
