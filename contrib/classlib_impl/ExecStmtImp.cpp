/*
 * ExecStmtImp.cpp
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
 *  Created on: Aug 29, 2016
 *      Author: ballance
 */

#include "ExecStmtImp.h"

namespace pss {

ExecStmtImp::ExecStmtImp(StmtType type) : m_refcnt(0), m_type(type) { }

ExecStmt::ExecStmt(const ExecStmt &rhs) {
	m_imp = rhs.m_imp;
	m_imp->inc_refcnt();
}

ExecStmt::ExecStmt(ExecStmtImp *imp) {
	m_imp = imp;
	m_imp->inc_refcnt();
}

ExecStmt::~ExecStmt() {
	m_imp->dec_refcnt();
}

ExecStmtImp *ExecStmt::imp() const {
	return m_imp;
}

ExecStmtImp::~ExecStmtImp() {
	// TODO Auto-generated destructor stub
}

void ExecStmtImp::inc_refcnt() {
	m_refcnt++;
}

void ExecStmtImp::dec_refcnt() {
	m_refcnt--;

	if (m_refcnt == 0) {
		delete this;
	}
}

} /* namespace pss */
