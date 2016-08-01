/*
 * LiteralImpl.h
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
 *  Created on: May 4, 2016
 *      Author: ballance
 */

#ifndef IMPL_LITERALIMPL_H_
#define IMPL_LITERALIMPL_H_
#include <string>
#include "api/ILiteral.h"

using namespace psi_api;

namespace psi {

class LiteralImpl : public ILiteral {
public:
	LiteralImpl(int64_t v);

	LiteralImpl(uint64_t v);

	LiteralImpl(bool v);

	LiteralImpl(const std::string &s);

	virtual ~LiteralImpl();

	virtual ExprType getType() const { return IExpr::ExprType_Literal; }

	virtual LiteralType getLiteralType() const { return m_literalType; }

	virtual int64_t getInt() const { return (int64_t)m_intval; }

	virtual uint64_t getBit() const { return m_intval; }

	virtual bool getBool() const { return (m_intval)?true:false; }

	virtual const std::string &getString() const { return m_strval; }


private:
	ILiteral::LiteralType			m_literalType;
	uint64_t						m_intval;
	std::string						m_strval;

};

} /* namespace psi */

#endif /* IMPL_LITERALIMPL_H_ */
