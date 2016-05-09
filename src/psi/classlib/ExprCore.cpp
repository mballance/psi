/*
 * ExprCore.cpp
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
 *  Created on: Apr 27, 2016
 *      Author: ballance
 */

#include "classlib/ExprCore.h"

#include "classlib/Expr.h"

namespace psi {

ExprCore::ExprCore(uint32_t v) : m_op(Expr::LiteralUint) {
	m_val.ui = v;
}

ExprCore::ExprCore(int32_t v) : m_op(Expr::LiteralInt) {
	m_val.i = v;
}

ExprCore::ExprCore(const Type &t) : m_op(Expr::TypeRef) {
	m_val.ref = &t;
}

ExprCore::ExprCore(Expr::Operator op) : m_op(op) { }

ExprCore::ExprCore(Expr::Operator op, const Expr &lhs, const Expr &rhs) :
	m_op(op), m_lhs(lhs), m_rhs(rhs) {
}

ExprCore::~ExprCore() {
	// TODO Auto-generated destructor stub
}

} /* namespace psi */
