/*
 * BinaryExprImpl.h
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

#ifndef IMPL_BINARYEXPRIMPL_H_
#define IMPL_BINARYEXPRIMPL_H_

#include "api/IBinaryExpr.h"

using namespace psi_api;

namespace psi {

class BinaryExprImpl: public IBinaryExpr {
public:
	BinaryExprImpl(
			IExpr					*lhs,
			IBinaryExpr::BinOpType 	op,
			IExpr					*rhs);

	virtual ~BinaryExprImpl();

	virtual ExprType getType() const { return IExpr::ExprType_BinOp; }

	virtual BinOpType getBinOpType() const { return m_op; }

	virtual IExpr *getLHS() const { return m_lhs; }

	virtual IExpr *getRHS() const { return m_rhs; }

private:

	IExpr									*m_lhs;
	IExpr									*m_rhs;
	IBinaryExpr::BinOpType					m_op;

};

} /* namespace psi */

#endif /* IMPL_BINARYEXPRIMPL_H_ */
