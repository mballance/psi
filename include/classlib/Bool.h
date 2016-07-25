/*
 * Bool.h
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
 *  Created on: Apr 28, 2016
 *      Author: ballance
 */

#ifndef SRC_CLASSLIB_BOOL_H_
#define SRC_CLASSLIB_BOOL_H_

#include <string>

#include "classlib/NamedBaseItem.h"
#include "classlib/Scope.h"

namespace psi {

class Bool: public NamedBaseItem {

	public:
		Bool(const Scope &p);

		/**
		 * This constructor is used for composing parameter lists.
		 * The name is that of the parameter
		 */
		Bool(const std::string &name);

		virtual ~Bool();

		/**
		 * The get method returns the solve-time value of this
		 * data field. Calling this method is only valid on
		 * fields of this type, and from within an inline-exec callback
		 */
		bool get();

		/**
		 * The set method sets the value of this data field.
		 * Calling this method is only valid on fields
		 * of this type, and only from within an
		 * inline-exec callback.
		 */
		void set(bool v);

	private:
		std::string					m_name;

};

} /* namespace psi */

#endif /* SRC_CLASSLIB_BOOL_H_ */
