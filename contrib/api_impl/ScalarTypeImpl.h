/*
 * ScalarTypeImpl.h
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
 *  Created on: May 6, 2016
 *      Author: ballance
 */

#ifndef IMPL_SCALARTYPEIMPL_H_
#define IMPL_SCALARTYPEIMPL_H_
#include "api/IScalarType.h"

using namespace psi_api;

namespace psi {

class ScalarTypeImpl: public IScalarType {
public:
	ScalarTypeImpl(
			IScalarType::ScalarType			scalar_type,
			uint32_t						msb,
			uint32_t						lsb);

	virtual ~ScalarTypeImpl();

	virtual ItemType getType() const { return IBaseItem::TypeScalar; }

	virtual IBaseItem *clone();

	virtual IBaseItem *getParent() const { return 0; }

	void setParent(IBaseItem *p) { }

	virtual ScalarType getScalarType() const { return m_scalarType; }

	/**
	 * Returns the MSB of the type for Bit and Int types
	 */
	virtual uint32_t getMSB() const { return m_msb; }

	/**
	 * Returns the LSB of the type for Bit and Int types
	 */
	virtual uint32_t getLSB() const { return m_lsb; }


private:
	IScalarType::ScalarType			m_scalarType;
	uint32_t						m_msb;
	uint32_t						m_lsb;
};

} /* namespace psi */

#endif /* IMPL_SCALARTYPEIMPL_H_ */
