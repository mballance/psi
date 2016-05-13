/*
 * ConstraintIfImpl.cpp
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

#include "ConstraintIfImpl.h"

namespace psi {

ConstraintIfImpl::ConstraintIfImpl(IExpr *cond, IConstraint *true_c, IConstraint *false_c) :
	m_cond(cond), m_true(true_c), m_false(false_c) { }

ConstraintIfImpl::~ConstraintIfImpl() {
	// TODO Auto-generated destructor stub
}

IBaseItem *ConstraintIfImpl::clone() {
	// TODO:
	return 0;
}

} /* namespace psi */
