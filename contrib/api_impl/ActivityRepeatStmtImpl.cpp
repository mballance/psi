/*
 * ActivityRepeatStmtImpl.cpp
 *
 * Copyright 2016 Mentor Graphics Corporation
 * All Rights Reserved Worldwide
 *
 * Licensed under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in
 *  compliance with the License.  You may obtain a copy of
 *  the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in
 * writing, software distributed under the License is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.  See
 * the License for the specific language governing
 * permissions and limitations under the License.
 * 
 *  Created on: Jun 10, 2016
 *      Author: ballance
 */

#include "../api_impl/ActivityRepeatStmtImpl.h"

namespace psi {

ActivityRepeatStmtImpl::ActivityRepeatStmtImpl(RepeatType type, IExpr *cond, IGraphStmt *stmt) :
	m_type(type), m_cond(cond), m_body(stmt) {
}

ActivityRepeatStmtImpl::~ActivityRepeatStmtImpl() {
	// TODO Auto-generated destructor stub
}

void ActivityRepeatStmtImpl::setBody(IGraphStmt *s) {
	m_body = s;
}

} /* namespace psi */
