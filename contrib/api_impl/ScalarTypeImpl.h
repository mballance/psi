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
#include "BaseItemImpl.h"

using namespace psi_api;

namespace psi {

class ScalarTypeImpl:
		public virtual IScalarType,
		public virtual BaseItemImpl {
public:
	ScalarTypeImpl(
			IScalarType::ScalarType			scalar_type,
			IExpr							*msb,
			IExpr							*lsb);

	virtual ~ScalarTypeImpl();

	virtual ScalarType getScalarType() const { return m_scalarType; }

	/**
	 * Returns the MSB of the type for Bit and Int types
	 */
	virtual IExpr *getMSB() const { return m_msb; }

	/**
	 * Returns the LSB of the type for Bit and Int types
	 */
	virtual IExpr *getLSB() const { return m_lsb; }


private:
	IScalarType::ScalarType			m_scalarType;
	IExpr							*m_msb;
	IExpr							*m_lsb;
};

} /* namespace psi */

#endif /* IMPL_SCALARTYPEIMPL_H_ */
