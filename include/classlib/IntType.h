/*
 * IntType.h
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
 *  Created on: Apr 24, 2016
 *      Author: ballance
 */

#ifndef INTTYPE_H_
#define INTTYPE_H_
#include <string>

#include "classlib/NamedBaseItem.h"

namespace psi {

class IntType : public NamedBaseItem {

	public:
		IntType(
				BaseItem 			*p,
				uint32_t			msb,
				uint32_t			lsb);

		IntType(
				const std::string	&name,
				uint32_t			msb,
				uint32_t			lsb);

		virtual ~IntType();

		uint32_t getMsb() const { return m_msb; }

		uint32_t getLsb() const { return m_lsb; }

	private:

		uint32_t					m_msb;
		uint32_t					m_lsb;
};

} /* namespace psi */

#endif /* INTTYPE_H_ */
